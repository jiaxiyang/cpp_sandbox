g++ -o test test.cpp

# 查看符号表
nm -C test
nm -C -f sysv test

# 查看符号大小
nm -C -S --size-sort test # 只显示当前模块定义的符号
readelf -s test

## 不加#include<iostream>无GLIBC++
nm -C test | grep GLIBC
readelf -s test | grep GLIBC
objdump -t test | grep GLIBC

# 查看节大小
size test
size -A test

# 查看节(section)信息
readelf -S test

# 查看段(segmant)信息和section to segment信息
readelf -l test

# 看进程映射区域
# cat /proc/pid/maps 或 pmap pid
# ./test
