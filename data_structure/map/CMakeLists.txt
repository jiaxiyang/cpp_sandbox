cmake_minimum_required(VERSION 3.8)

project(map)

# # lib add_library(map SHARED) target_sources(map PRIVATE src/map.cpp)
# target_compile_options(map PRIVATE -O3 -std=c++17)
# target_include_directories(map PUBLIC include) find_package(glog REQUIRED)
# target_link_libraries(map PRIVATE glog::glog)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
# example
list(APPEND GRAPH_EXAMPLES map_example unordered_map_example)
foreach(example IN LISTS GRAPH_EXAMPLES)
  add_executable(${example} examples/${example}.cpp)
  target_compile_options(${example} PRIVATE -O3 -std=c++17 -pg)
endforeach()

# add_executable(map_example) target_sources(map_example PRIVATE
# example/:map_example.cpp) target_link_libraries( map_example PUBLIC map
# PRIVATE glog::glog)
