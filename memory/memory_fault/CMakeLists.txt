cmake_minimum_required(VERSION 3.8)

project(test)

# lib
add_executable(test)
target_sources(test PRIVATE test.cpp)
