cmake_minimum_required(VERSION 3.8)

project(queue)

# example
list(APPEND GRAPH_EXAMPLES queue_example deque_example)
foreach(example IN LISTS GRAPH_EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
endforeach()

# add_executable(queue_example) target_sources(queue_example PRIVATE
# example/:queue_example.cpp) target_link_libraries( queue_example PUBLIC queue
# PRIVATE glog::glog)
