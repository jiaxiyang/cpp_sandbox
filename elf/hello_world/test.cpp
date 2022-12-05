
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

int get() { return 1; }

// static int a = 0;
// static int b = 0;
// static int c = 0;
int d = 0; //.bss
int e = 1; //.data
int in_bigvar_bss[16300];
// int bigvar_in_data[16300] = {1};
// int var_in_data[5] = {1, 2, 3, 4, 5};
int main(int argc, char *argv[]) {
  // 1. nm -C -S  --size-sort test 查看变量地址
  // 2. cat /proc/pid/maps映射地址，可以看到d, e地址与在map中的地址与nm
  // 地址偏移一样
  // 3. 多次运行，d, e地址不一样
  std::cout << (void *)&d << std::endl;
  std::cout << (void *)&e << std::endl;

  int *new_test = new int[10000];
  std::cout << (void *)&new_test << std::endl; // new_test point is on stack
  std::cout << &(*new_test) << std::endl; // new_test data address is on heap
  delete[] new_test;

  int *malloc_test = (int *)malloc(100000);
  std::cout << (void *)&malloc_test
            << std::endl; // malloc_test point is on stack
  std::cout << &(*malloc_test)
            << std::endl; // malloc_test data address is on heap
  free(malloc_test);

  while (true) {
    sleep(1);
  }

  return 0;
}
