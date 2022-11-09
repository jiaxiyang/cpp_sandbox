set(GIT_VERSION "unknown")

find_package(Git QUIET)
if(GIT_FOUND)
  # execute_process( COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --long
  # OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
  execute_process(
    COMMAND git describe --always --dirty --long
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE)

endif()

if("${GIT_VERSION_SHORT}" STREQUAL "")
  execute_process(
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND git rev-parse HEAD
    OUTPUT_VARIABLE GIT_VERSION_SHORT)
endif()
string(STRIP "${GIT_VERSION_SHORT}" GIT_VERSION_SHORT)

message(STATUS "Git hash is ${GIT_VERSION}")
# message(STATUS "Git hash is ${GIT_VERSION_SHORT}")
include(${CURRENT_BINARY_DIR}/version.c.kv)
string(TIMESTAMP BUILT_TIME "%Y-%m-%d %H:%M:%S [UTC]" UTC)

message(STATUS "CURRENT_BINARY_DIR:  ${CURRENT_BINARY_DIR}")
configure_file(${CMAKE_CURRENT_LIST_DIR}/version.c.in
               ${CURRENT_BINARY_DIR}/version.c @ONLY)
