add_library(dog SHARED)
# add_library(dog STATIC)
target_sources(dog PRIVATE src/dog.cpp src/dog1.cpp)
target_compile_options(dog PRIVATE -O3 -std=c++17)
target_include_directories(dog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_libraries(dog PUBLIC -Wl,--whole-archive animal
# -Wl,-no-whole-archive)
target_link_libraries(dog PUBLIC animal)

add_executable(dog_test)
target_sources(dog_test PRIVATE test/test.cpp)
target_link_libraries(dog_test PUBLIC dog)

# // diff UT, 如果不使用libdog.so中的符号，libdog.so不会被初始化，随便使用libdog.so中的一个符号，全局变量就会初始化。
add_executable(dog_test1)
target_sources(dog_test1 PRIVATE test/test1.cpp)
# target_link_libraries(dog_test1 PUBLIC -Wl,--whole-archive dog
# -Wl,-no-whole-archive)
target_link_libraries(dog_test1 PUBLIC dog dl)

# // same UT 变量不管是否使用， 都会初始化，因为用到可当前库的符号 add_executable(dog_test2)
# target_sources(dog_test2 PRIVATE src/dog.cpp test/test1.cpp)
# target_compile_options(dog_test2 PRIVATE -O3 -std=c++17)
# target_include_directories(dog_test2 PUBLIC
# ${CMAKE_CURRENT_SOURCE_DIR}/include) target_link_libraries(dog_test2 PUBLIC
# animal glog)
