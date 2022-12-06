#!/bin/bash

BUILD_TYPE=Release
BUILD_DIR=build
BUILD_SYSTEM='Unix Makefiles'
rm -rf ${BUILD_DIR}
cmake -G "${BUILD_SYSTEM}" -S . -B ${BUILD_DIR} \
	-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build ${BUILD_DIR}

# Static application security testing (SAST)
run-clang-tidy -p ${BUILD_DIR} -header-filter=.* # need compile_compile.json

# clang-tidy -list-checks # list check
# clang-tidy -checks=* test.cpp -- # check all
# clang-tidy test.cpp -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus* --
# clang-tidy -checks=-*,clang-analyzer-*,clang-analyzer-cplusplus*,performance-*, test.cpp --
# clang-tidy -checks=-*,clang-analyzer-*,-clang-analyzer-cplusplus*, test.cpp --
# clang-tidy -checks=-*,clang-analyzer-* test.cpp -- # can check memory leak
# fdfind --type f '.*\.(c|cpp|h|hpp|hxx|cxx)' | xargs -I {} clang-tidy -checks=-*,clang-analyzer-* {} --

# cppcheck test.cpp
# cpplint test.cpp

# g++ -g -o test test.cpp
# g++ -o test test.cpp # coredump no source info

./${BUILD_DIR}/test
# gdb ./test core...
# bt
