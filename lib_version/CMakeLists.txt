cmake_minimum_required(VERSION 3.8)

project(version)
include(cmake/common.cmake)
# libgraph
add_library(version SHARED)
target_sources(version PRIVATE src/version.cpp)
config_version_support(version)
# target_sources(version PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/version.c)
target_compile_options(version PRIVATE -O3 -std=c++17)
target_include_directories(version PUBLIC include)

# 注意一个文件夹一个comonent, 对应一个version
add_subdirectory(component1)

add_executable(version_example)
target_sources(version_example PRIVATE example/version_example.cpp)
target_link_libraries(version_example PRIVATE dl version version1)
config_version_support(version_example)
