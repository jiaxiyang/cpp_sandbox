# -g 才能显示在哪一行内存泄漏
g++ -g -o test test.cpp
file test                    # show with debug_info
readelf -S test | grep debug # must have debug info

# 定位动态库内存泄漏
# LD_PRELOAD=xxx.so valgrind ...

valgrind \
	--tool=memcheck \
	--leak-check=full \
	--track-origins=yes \
	--show-leak-kinds=all \
	--num-callers=10 \
	./test
# --verbose \
# --log-file=valgrind.log \
# --keep-debuginfo=yes \ # for shared library;only some version can use
