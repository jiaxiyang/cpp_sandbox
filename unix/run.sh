#!/bin/bash

BUILD_TYPE=Release
BUILD_DIR=build
INSTALL_DIR=${BUILD_DIR}/$(basename "$PWD")_$(echo ${BUILD_TYPE} | tr '[:upper:]' '[:lower:]')
BUILD_SYSTEM='Unix Makefiles'

rm -rf ${BUILD_DIR}

cmake -G "${BUILD_SYSTEM}" -S . -B ${BUILD_DIR} \
	-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DCMAKE_VERBOSE_MAKEFILE=ON

cmake --build ${BUILD_DIR}
mv ${BUILD_DIR}/compile_commands.json .

./${BUILD_DIR}/ls .
