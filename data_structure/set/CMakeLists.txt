cmake_minimum_required(VERSION 3.8)

project(set)

# lib add_library(set SHARED) target_sources(set PRIVATE src/set.cpp)
# target_compile_options(set PRIVATE -O3 -std=c++17)
# target_include_directories(set PUBLIC include) find_package(glog REQUIRED)
# target_link_libraries(set PRIVATE glog::glog)

# example
list(APPEND GRAPH_EXAMPLES set_example)
foreach(example IN LISTS GRAPH_EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
  # target_link_libraries(${example} PUBLIC set)
endforeach()

# add_executable(set_example) target_sources(set_example PRIVATE
# example/:set_example.cpp) target_link_libraries( set_example PUBLIC set
# PRIVATE glog::glog)
