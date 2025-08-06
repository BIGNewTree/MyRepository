# ThreadPool - 一个高效的C++11线程池实现

## 概述
- 这个项目实现了一个基于C++11标准的高性能线程池，具有任务队列、工作线程管理和异步任务提交等功能。它使用了现代C++特性如右值引用、完美转发和future/promise模式，能够高效地处理并发任务。

## 特性：
- 基于C++11标准实现
- 支持任意返回类型的任务提交
- 使用条件变量实现任务队列的高效等待
- 支持线程安全的队列操作
- 提供方便的线程池关闭机制

## 安装
### 1.项目结构建议​​
```
ThreadPool/
├── CMakeLists.txt
├── ThreadPool.h
├── ThreadPool.cpp
└── demo.cpp (示例程序，可选)
```
### 2. 构建命令
```bash
cd ThreadPool
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
### 3. 安装选项
```bash
cmake --install . --prefix=/usr/local  # Linux/macOS
```

## 关键技术解析：
### 1. 右值引用与完美转发
在SubMit方法中，我们使用了模板和完美转发来支持任意参数类型的任务:
```cpp
template <typename F, typename... Args>
auto SubMit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
{
    // ...
    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    // ...
}
```
- F&&和Args&&...是通用引用(Universal Reference)，可以接受左值或右值。
- std::forward保持参数的原始值类别(左值/右值)。
- 这种技术避免了不必要的拷贝，提高了性能。

### 2. std::packaged_task与std::future
```cpp
auto task = std::make_shared<std::packaged_task<ReturnType()>>(
    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
);
```
- std::future<ReturnType> res = task->get_future();
- std::packaged_task包装可调用对象，允许异步获取结果
- std::future提供异步结果获取机制
- 使用shared_ptr管理packaged_task的生命周期

### 3. 条件变量与锁
```cpp
std::unique_lock<std::mutex> lock(m_mtx);
m_cv.wait(lock, [this] { return !m_queue.empty() || m_shutdown; });
```
- std::condition_variable实现线程间的同步
- std::unique_lock提供灵活的锁管理
- 使用谓词防止虚假唤醒

### 4. 移动语义
```cpp
ThreadPool(ThreadPool&&) = delete;
ThreadPool& operator=(ThreadPool&&) = delete;
```

- 显式删除移动构造函数和移动赋值运算符
- 确保线程池对象的唯一所有权

## 性能考虑
- `任务队列​​`：使用std::queue和互斥锁实现线程安全队列
- `线程管理`：工作线程在空闲时阻塞，避免CPU空转
- `资源获取`​​：使用RAII管理锁资源，避免死锁

## 贡献指南
- 欢迎提交Pull Request。对于重大更改，请先开Issue讨论。

## 许可证

MIT License


