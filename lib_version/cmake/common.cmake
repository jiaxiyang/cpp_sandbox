function(_get_all_properties target_name)
  set(_RET "")
  foreach(_prop ${CMAKE_PROPERTY_LIST})
    string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" _prop ${_prop})
    # Fix
    # https://stackoverflow.com/questions/32197663/how-can-i-remove-the-the-location-property-may-not-be-read-from-target-error-i
    if(_prop STREQUAL "LOCATION"
       OR _prop MATCHES "^LOCATION_"
       OR _prop MATCHES "_LOCATION$")
      continue()
    endif()
    get_property(
      _propval
      TARGET ${target_name}
      PROPERTY ${_prop}
      SET)
    if(_propval)
      get_target_property(_propval ${target_name} ${_prop})
      _kv(${target_name} ${_prop} "${_propval}")
    else(_propval)
      _kv(${target_name} ${_prop} "${_propval}")
    endif(_propval)
  endforeach(_prop)
  set(${result}
      ${_RET}
      PARENT_SCOPE)
endfunction(_get_all_properties)

function(_kv target_name k v)
  file(
    APPEND
    ${CMAKE_CURRENT_BINARY_DIR}/version_src/${target_name}_version/version.c.kv
    "set(" ${k} " [=[" "${v}" "]=])" \n)
endfunction(_kv)

function(_k target_name k)
  file(
    APPEND
    ${CMAKE_CURRENT_BINARY_DIR}/version_src/${target_name}_version/version.c.kv
    "set(" ${k} " [=[" ${${k}} "]=])" \n)
endfunction(_k)

function(config_version_support target_name)
  file(
    WRITE
    ${CMAKE_CURRENT_BINARY_DIR}/version_src/${target_name}_version/version.c.kv
    "# export variables for versio info" \n)
  _get_all_properties(${target_name} _properties)
  _k(${target_name} PROJECT_NAME)
  _kv(${target_name} COMPONENT_NAME ${target_name})
  _kv(${target_name} TARGET_NAME ${target_name})
  _kv(${target_name} BUILD_ID "$ENV{BUILD_ID}")
  _kv(${target_name} BUILD_USER "$ENV{USER}")
  _kv(${target_name} CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
  _k(${target_name} CMAKE_CXX_FLAGS)
  _k(${target_name} CMAKE_CXX_FLAGS_DEBUG)
  get_cmake_property(_variableNames VARIABLES)
  foreach(_variableName ${_variableNames})
    _k(${target_name} ${_variableName})
  endforeach()
  foreach(
    _info
    OS_NAME
    OS_RELEASE
    OS_VERSION
    OS_PLATFORM
    FQDN
    PROCESSOR_SERIAL_NUMBER
    PROCESSOR_NAME
    PROCESSOR_DESCRIPTION)
    cmake_host_system_information(RESULT _r QUERY ${_info})
    message(STATUS "_info ${_info} _r ${_r}")
    _kv(${target_name} ${_info} ${_r} "")
  endforeach(_info)

  message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
  file(MAKE_DIRECTORY
       "${CMAKE_CURRENT_BINARY_DIR}/version_src/${target_name}_version")
  add_custom_command(
    OUTPUT
      ${CMAKE_CURRENT_BINARY_DIR}/version_src/${target_name}_version/version.c
    COMMAND
      ${CMAKE_COMMAND} -DCURRENT_KV_DIR=${CMAKE_CURRENT_BINARY_DIR}
      -DCURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}/version_src/${target_name}_version
      -P ${CMAKE_SOURCE_DIR}/cmake/version.cmake
    DEPENDS
      ${CMAKE_CURRENT_BINARY_DIR}/version_src/${target_name}_version/version.c.kv
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  target_sources(
    ${target_name}
    PRIVATE
      ${CMAKE_CURRENT_BINARY_DIR}/version_src/${target_name}_version/version.c)
endfunction(config_version_support)

if(NOT version_tool)
  configure_file(${CMAKE_CURRENT_LIST_DIR}/version_tool.cpp
                 ${CMAKE_BINARY_DIR}/version_tool.cpp @ONLY)
  add_executable(version_tool)
  target_sources(version_tool PRIVATE ${CMAKE_BINARY_DIR}/version_tool.cpp)
  target_link_libraries(version_tool PRIVATE dl)
  config_version_support(version_tool)
  install(TARGETS version_tool DESTINATION bin)
endif()
