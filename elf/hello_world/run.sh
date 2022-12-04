g++ -o test test.cpp

# 查看符号表
nm -C test

## 不加#include<iostream>无GLIBC++
nm -C test | grep GLIBC
readelf -s test | grep GLIBC
objdump -t test | grep GLIBC

# 查看节(section)信息
readelf -S test

# 查看节大小
size test
size -A test

# 查看段(section)信息
readelf -l test

# 查看各个段内存地址
