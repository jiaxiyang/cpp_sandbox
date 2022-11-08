cmake_minimum_required(VERSION 3.8)

include(CMakePrintHelpers)

cmake_print_variables(CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if(${CMAKE_BUILD_TYPE} MATCHES Debug)
  message(WARNING "Build type: ${CMAKE_BUILD_TYPE}")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
endif()

add_library(animal SHARED)
# add_library(animal STATIC)

# source
target_sources(animal PRIVATE src/animal.cpp)

# compile set(CMAKE_CXX_COMPILER "g++")
target_compile_options(animal PRIVATE -O3 -std=c++17)

# link
find_package(glog REQUIRED)
target_include_directories(animal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(animal glog::glog)

install(TARGETS animal DESTINATION lib)

# package
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}")
include(CPack)

add_executable(animal_test test/test.cpp)
target_link_libraries(animal_test PRIVATE animal)
