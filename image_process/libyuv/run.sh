#!/bin/bash

BUILD_TYPE=Release
BUILD_DIR=build
INSTALL_DIR=${BUILD_DIR}/$(basename "$PWD")_$(echo ${BUILD_TYPE} | tr '[:upper:]' '[:lower:]')
BUILD_SYSTEM='Unix Makefiles'

rm -rf ${BUILD_DIR}

cmake -G "${BUILD_SYSTEM}" -S . -B ${BUILD_DIR} \
	-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
	-DCMAKE_VERBOSE_BUILD=OFF \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
	-DCMAKE_VERBOSE_MAKEFILE=OFF
# -DCMAKE_C_COMPILER=clang \
# -DCMAKE_CXX_COMPILER=clang++

cmake --build ${BUILD_DIR}
LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH ./${BUILD_DIR}/yuv_crop_example
md5sum libyuv_nv12_center_crop1.yuv
md5sum libyuv_nv12_center_crop2.yuv
