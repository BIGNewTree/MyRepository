#include <iostream>
#include <mutex>
#include <vector>
#include <queue>
#include <condition_variable>
#include <future>
#include <functional>

template<typename T>
class LockQueue
{
public:
    LockQueue() {}
    LockQueue(const LockQueue& ) {}
    ~LockQueue() {}


public:
    void Push(const T& data)
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_queue.push(data);
        m_size++;
        m_cv.notify_one();
    }

    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        while(m_queue.empty())
        {
            m_cv.wait(lock);
        }
        T data = m_queue.front();
        m_queue.pop();
        m_size--;
        return data;
    }

    bool Empty()
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        return m_queue.empty();
    }

    int Size()
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        return m_size;
    }

    bool TimeOutPop(int timeout, T* ResData)
    {
        std::unique_lock<std::mutex> lock(m_mtx);

        auto now = std::chrono::system_clock::now();
        auto timeout_time = now + std::chrono::milliseconds(timeout);

        while(m_queue.empty())
        {
            if(m_cv.wait_until(lock, timeout_time) == std::cv_status::timeout)
            {
                return false;
            }
        }

        T data = m_queue.front();
        m_queue.pop();
        m_size--;
        *ResData = data;
        return true;
    }


private:
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::queue<T> m_queue; // 任务队列
    int m_size;
};

class ThreadPool
{

private:
// 内置工作线程
class ThreadWorker
{
public:
    ThreadWorker(ThreadPool* pool, const int id) : m_pool(pool), m_id(id) {}

    void operator()()
    {
        std::function<void()> func; // 定义基础函数类func

        bool dequeued; // 是否正在取出队列中的元素

        while(!m_pool->m_shutdown) // 未关闭线程池
        {
            {
                std::unique_lock<std::mutex> lock(m_pool->m_mtx);
                while(m_pool->m_task.Empty() && !m_pool->m_shutdown) // 若任务队列为空， 阻塞当前线程
                {
                    m_pool->m_cv.wait(lock);
                }

                func = m_pool->m_task.Pop(); // 取工作函数
            }

            func(); // 执行工作函数
        }
    }


private:
    ThreadPool* m_pool; // 所属线程池
    int m_id; // 工作id
};

public:
    ThreadPool(const int threadNum = 4) : m_threads(std::vector<std::thread>(threadNum)), m_shutdown(false) {}

    ThreadPool(const ThreadPool& ) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool& ) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    void init()
    {
        for(int i = 0; i < m_threads.size(); i++)
        {
            m_threads.at(i) = std::thread(ThreadWorker(this, i)); // 分配工作线程
        }
    }

    void ShutDown()
    {
        m_shutdown = true;
        m_cv.notify_all();

        for(auto& thread : m_threads)
        {
            if(thread.joinable()) // 判断线程是否在等待
            {
                thread.join();
            }
        }
    }

    template <typename F, typename... Args>
    auto SubMit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        std::function<void()> func_task = [task_ptr]()
        {
            (*task_ptr)();
        };

        m_task.Push(func_task);

        m_cv.notify_one();

        return task_ptr->get_future();
    }

private:
    bool m_shutdown; // 线程池是否关闭
    LockQueue<std::function<void()>> m_task; // 任务队列
    std::vector<std::thread> m_threads; // 工作线程数组
    std::mutex m_mtx;
    std::condition_variable m_cv;
};