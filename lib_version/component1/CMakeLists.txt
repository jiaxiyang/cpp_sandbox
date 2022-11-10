add_library(version1 SHARED)
target_sources(version1 PRIVATE src/version1.cpp)
target_link_libraries(version1 PUBLIC version)
config_version_support(version1)
