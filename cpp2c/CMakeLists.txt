# cmake_minimum_required(VERSION 3.8)

# project(graph)

# # libgraph add_library(graph SHARED) target_sources(graph PRIVATE src/graph.cc
# src/graph_imp.cc) target_compile_options(graph PRIVATE -O3 -std=c++17)
# target_include_directories(graph PUBLIC include) find_package(glog REQUIRED)
# target_link_libraries(graph PRIVATE glog::glog)

# # example add_executable(graph_example) target_sources(graph_example PRIVATE
# example/graph_example.cc) target_link_libraries( graph_example PUBLIC graph
# PRIVATE glog::glog)

# add_executable(graph_example_dl) target_sources(graph_example_dl PRIVATE
# example/graph_example_dl.cc) target_link_libraries( graph_example_dl PUBLIC
# graph PRIVATE glog::glog dl)

cmake_minimum_required(VERSION 3.8)

project(graph)

# libgraph
add_library(graph SHARED)
target_sources(graph PRIVATE src/graph.cc src/graph_imp.cc)
target_compile_options(graph PRIVATE -O3 -std=c++17)
target_include_directories(graph PUBLIC include)
find_package(glog REQUIRED)
target_link_libraries(graph PRIVATE glog::glog)

# example
add_executable(graph_example)
target_sources(graph_example PRIVATE example/graph_example.cc)
target_link_libraries(
  graph_example
  PUBLIC graph
  PRIVATE glog::glog)
