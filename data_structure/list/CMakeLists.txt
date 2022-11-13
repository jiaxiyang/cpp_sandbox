cmake_minimum_required(VERSION 3.8)

project(list)

# lib add_library(list SHARED) target_sources(list PRIVATE src/list.cpp)
# target_compile_options(list PRIVATE -O3 -std=c++17)
# target_include_directories(list PUBLIC include) find_package(glog REQUIRED)
# target_link_libraries(list PRIVATE glog::glog)

# example
list(APPEND GRAPH_EXAMPLES list_example)
foreach(example IN LISTS GRAPH_EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
  # target_link_libraries(${example} PUBLIC list)
endforeach()

# add_executable(list_example) target_sources(list_example PRIVATE
# example/:list_example.cpp) target_link_libraries( list_example PUBLIC list
# PRIVATE glog::glog)
