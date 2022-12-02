cmake_minimum_required(VERSION 3.8)

project(unix)

# example
list(APPEND EXAMPLES ls)
foreach(example IN LISTS EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
  target_include_directories(${example} PRIVATE third_party/apue.3e/include)
  # target_link_directories(${example} PRIVATE third_party/apue.3e/lib)
  # target_link_libraries(${example} PUBLIC apue)
endforeach()
