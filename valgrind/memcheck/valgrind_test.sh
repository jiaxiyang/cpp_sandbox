#!/bin/bash

if ! [ -x "$(command -v valgrind)" ]; then
	echo "Can't find valgrind, install: sudo apt install valgrind-dbg"
fi

cat >valgrind_test.cpp <<EOF
int main(){
    int *test = new int[1];
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
	--num-callers=10 \
	./valgrind_test
# --verbose \
# --log-file=valgrind.log \
