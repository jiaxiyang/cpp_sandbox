cmake_minimum_required(VERSION 3.8)

project(tree)

# example
list(APPEND GRAPH_EXAMPLES tree_example)
foreach(example IN LISTS GRAPH_EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
endforeach()
