cmake_minimum_required(VERSION 3.8)

project(yuv)

# example
list(APPEND EXAMPLES yuv_crop_example)
foreach(example IN LISTS EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
  target_compile_options(${example} PRIVATE -O3 -std=c++17)
  target_link_libraries(${example} PRIVATE yuv glog jpeg)
endforeach()

# add_executable(yuv_example) target_sources(yuv_example PRIVATE
# example/:yuv_example.cpp) target_link_libraries( yuv_example PUBLIC yuv
# PRIVATE glog::glog)
