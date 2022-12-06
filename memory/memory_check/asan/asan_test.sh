#!/bin/bash

# if ! [ -x "$(command -v valgrind)" ]; then
# 	echo "Can't find valgrind, install: sudo apt install valgrind-dbg"
# fi

cat >asan_test.cpp <<EOF
#include <stdlib.h>
#include <vector>
#include <iostream>

int main(){
    // memory leak
    int *test = new int[1];

    // double free
    // int *malloc_test = (int *)malloc(100000);
    // free(malloc_test);
    // free(malloc_test);

    // overflow buffer
    // std::vector<int> vec;
    // vec.push_back(2);
    // vec[11] = 100;

    // use not init buf
    std::vector<int> vec1;
    vec1.reserve(10);
    std::cout << vec1[0] << std::endl;
    return 0;
}
EOF

## man g++ to grep asan option

# -g 才能显示在哪一行内存泄漏 -fsanitize=address会生成其他debug信息
g++ -g -o asan_test asan_test.cpp -fsanitize=address # address也会查leak
# g++ -g -o asan_test asan_test.cpp -fsanitize=leak
# g++ -g -o asan_test asan_test.cpp -fsanitize=address -fsanitize=memory -fsanitize-memory-track-origins -lasan
file asan_test                    # show with debug_info
readelf -S asan_test | grep debug # must have debug info
./asan_test
# LD_DEBUG=libs ./asan_test
