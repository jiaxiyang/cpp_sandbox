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
      _kv(${_prop} "${_propval}")
    else(_propval)
      _kv(${_prop} "${_propval}")
    endif(_propval)
  endforeach(_prop)
  set(${result}
      ${_RET}
      PARENT_SCOPE)
endfunction(_get_all_properties)

function(_kv k v)
  file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/version.c.kv "set(" ${k} " [=["
                                                       "${v}" "]=])" \n)
endfunction(_kv)

function(_k k)
  file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/version.c.kv "set(" ${k} " [=["
                                                       ${${k}} "]=])" \n)
endfunction(_k)

function(config_version_support target_name)
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/version.c.kv
       "# export variables for versio info" \n)
  _get_all_properties(${target_name} _properties)
  _k(PROJECT_NAME)
  _kv(COMPONENT_NAME ${target_name})
  _kv(BUILD_ID "$ENV{BUILD_ID}")
  _kv(BUILD_USER "$ENV{USER}")
  _kv(CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
  _k(CMAKE_CXX_FLAGS)
  _k(CMAKE_CXX_FLAGS_DEBUG)
  get_cmake_property(_variableNames VARIABLES)
  foreach(_variableName ${_variableNames})
    _k(${_variableName})
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
    _kv(${_info} ${_r} "")
  endforeach(_info)

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/version.c
    COMMAND ${CMAKE_COMMAND} -DCURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR} -P
            ${CMAKE_SOURCE_DIR}/cmake/version.cmake
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/version.c.kv
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

  target_sources(${target_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/version.c)
endfunction(config_version_support)
