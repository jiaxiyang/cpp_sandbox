cmake_minimum_required(VERSION 3.8)

project(stack)

# lib add_library(stack SHARED) target_sources(stack PRIVATE src/stack.cpp)
# target_compile_options(stack PRIVATE -O3 -std=c++17)
# target_include_directories(stack PUBLIC include) find_package(glog REQUIRED)
# target_link_libraries(stack PRIVATE glog::glog)

# example
list(APPEND GRAPH_EXAMPLES stack_example)
foreach(example IN LISTS GRAPH_EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
endforeach()

# add_executable(stack_example) target_sources(stack_example PRIVATE
# example/:stack_example.cpp) target_link_libraries( stack_example PUBLIC stack
# PRIVATE glog::glog)
