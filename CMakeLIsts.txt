cmake_minimum_required(VERSION 3.12)
project(ThreadPool LANGUAGES CXX)

# 设置C++标准要求（兼容您的代码特性）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 配置编译选项
if(MSVC)
    add_compile_options(/W4 /WX /O2)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3 -pthread)
endif()

# 定义线程池库目标
add_library(ThreadPool
    ThreadPool.h
    ThreadPool.cpp
)

# 设置包含目录
target_include_directories(ThreadPool
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

# 链接系统线程库
find_package(Threads REQUIRED)
target_link_libraries(ThreadPool
    PUBLIC 
    Threads::Threads
)

# 可选：安装配置
install(TARGETS ThreadPool
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(FILES ThreadPool.h
    DESTINATION include
)

# 示例程序（可选）
add_executable(ThreadPoolDemo
    demo.cpp
)
target_link_libraries(ThreadPoolDemo
    PRIVATE 
    ThreadPool
)

# 支持ctest测试（可选）
enable_testing()
add_test(NAME ThreadPoolTest COMMAND ThreadPoolDemo)