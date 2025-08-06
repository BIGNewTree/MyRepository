#include <iostream>
#include <random>
#include <thread>
#include "threadpool.h"

std::random_device rd; // 真实随机数产生器

std::mt19937 mt(rd()); //生成计算随机数mt

std::uniform_int_distribution<int> dist(-1000, 1000); //生成-1000到1000之间的离散均匀分布数

auto rnd = std::bind(dist, mt);

// 设置线程睡眠时间
void simulate_hard_computation()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

// 添加两个数字的简单函数并打印结果
void multiply(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
}

// 添加并输出结果
void multiply_output(int &out, const int a, const int b)
{
    simulate_hard_computation();
    out = a * b;
    std::cout << a << " * " << b << " = " << out << std::endl;
}

// 结果返回
int multiply_return(const int a, const int b)
{
    simulate_hard_computation();
    const int res = a * b;
    std::cout << a << " * " << b << " = " << res << std::endl;
    return res;
}

void example()
{
    ThreadPool pool(3); // 创建有3个线程的线程池

    pool.init(); // 初始化

    for(int i = 0; i <= 3; i++)
    {
        for(int j = 1; j <= 10; j++)
        {
            pool.SubMit(multiply, i, j);
        }
    }

    int output_ref;
    auto future1 = pool.SubMit(multiply_output, std::ref(output_ref), 5, 6);

    future1.get();
    std::cout << "Last operation result is equals to " << output_ref << std::endl;

    auto future2 = pool.SubMit(multiply_return, 5, 3);

    int res = future2.get();
    std::cout << "Last operation result is equals to " << res << std::endl;

    pool.ShutDown();
}

int main()
{
    example();
    return 0;
}