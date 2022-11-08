cmake_minimum_required(VERSION 3.8)

project(singleton)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generate compile_comands.json

add_library(singleton STATIC)
target_sources(singleton PRIVATE src/singleton.cpp)
target_include_directories(singleton PUBLIC include)
# target_compile_options(singleton PRIVATE -O3 -std=c++17) 加了
# -fvisibility=hidden 后符号(Instance函数)被隐藏，有多份static局部变量，会有多个实例
target_compile_options(singleton PRIVATE -O3 -std=c++17 -fvisibility=hidden)
find_package(glog REQUIRED)
target_link_libraries(singleton glog::glog)

add_library(foo SHARED)
target_sources(foo PRIVATE src/foo.cpp)
target_include_directories(foo PUBLIC include)
target_compile_options(foo PRIVATE -O3 -std=c++17)
target_link_libraries(foo PUBLIC -Wl,--whole-archive singleton
                                 -Wl,-no-whole-archive)

add_executable(test_singleton test/test.cpp)
target_link_libraries(test_singleton foo -Wl,--whole-archive singleton
                      -Wl,-no-whole-archive)
