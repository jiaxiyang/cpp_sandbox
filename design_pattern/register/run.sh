#!/bin/bash

BUILD_TYPE=Release
BUILD_DIR=build
INSTALL_DIR=${BUILD_DIR}/$(basename "$PWD")_$(echo ${BUILD_TYPE} | tr '[:upper:]' '[:lower:]')
TARGET_NAME=
BUILD_SYSTEM=Ninja
if ! [ -x "$(command -v ninja)" ]; then
	BUILD_SYSTEM='Unix Makefiles'
fi
BUILD_SYSTEM='Unix Makefiles'

rm -rf ${BUILD_DIR}

cmake -G "${BUILD_SYSTEM}" -S . -B ${BUILD_DIR} \
	-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DCMAKE_VERBOSE_MAKEFILE=ON
# -DCMAKE_C_COMPILER=clang \
# -DCMAKE_CXX_COMPILER=clang++

cmake --build ${BUILD_DIR}
# cmake --build ${BUILD_DIR} --target ${TARGET_NAME}

#(cd ${BUILD_DIR} && make test)
# ctest --test-dir ${BUILD_DIR} # after cmake 3.20

#cmake --install ${BUILD_DIR} --strip --prefix ${INSTALL_DIR}

mv ${BUILD_DIR}/compile_commands.json .
#clang-tidy *.cpp

# cpack --config ${BUILD_DIR}/CPackConfig.cmake
readelf -d build/dog/dog_test | grep 'NEEDED'
./build/dog/dog_test

readelf -d build/dog/dog_test1 | grep 'NEEDED'
./build/dog/dog_test1

# sudo awk '/\.so/{print $6}' /proc/114023/maps | sort -u
# sudo lsof -p 1| grep mem | grep so
