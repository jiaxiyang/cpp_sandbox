cmake_minimum_required(VERSION 3.8)

project(graph)

# lib
add_library(graph SHARED)
target_sources(graph PRIVATE src/graph.cpp)
target_compile_options(graph PRIVATE -O3 -std=c++17)
target_include_directories(graph PUBLIC include)
find_package(glog REQUIRED)
target_link_libraries(graph PRIVATE glog::glog)

# example
list(APPEND GRAPH_EXAMPLES graph_example graph_example1 graph_example2)
foreach(example IN LISTS GRAPH_EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
  target_link_libraries(${example} PUBLIC graph)
endforeach()

# add_executable(graph_example) target_sources(graph_example PRIVATE
# example/:graph_example.cpp) target_link_libraries( graph_example PUBLIC graph
# PRIVATE glog::glog)
