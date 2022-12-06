#!/bin/bash

if ! [ -x "$(command -v valgrind)" ]; then
	echo "Can't find valgrind, install: sudo apt install valgrind-dbg"
fi

cat >valgrind_test.cpp <<EOF
#include <stdlib.h>
#include <vector>
#include <iostream>

int main(){
    // memory leak
    int *test = new int[1];

    // double free
    int *malloc_test = (int *)malloc(100000);
    free(malloc_test);
    free(malloc_test);

    // overflow buffer
    std::vector<int> vec;
    vec.push_back(2);
    vec[11] = 100;

    // use not init buf
    std::vector<int> vec1;
    vec1.reserve(10);
    std::cout << vec1[0] << std::endl;
    return 0;
}
EOF

# -g 才能显示在哪一行内存泄漏
g++ -g -o valgrind_test valgrind_test.cpp
file valgrind_test                    # show with debug_info
readelf -S valgrind_test | grep debug # must have debug info

# 定位动态库内存泄漏
# LD_PRELOAD=xxx.so valgrind ...

valgrind \
	--tool=memcheck \
	--leak-check=full \
	--track-origins=yes \
	--show-leak-kinds=all \
	./valgrind_test
# --num-callers=10 \ # stack size
# --verbose \
# --log-file=valgrind.log \
# --keep-debuginfo=yes \ # for shared library;only some version can use
