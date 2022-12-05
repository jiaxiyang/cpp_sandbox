// 1. Segmentation faults occur when accessing memory which does not belong to
// your process. They are very common and are typically the result of:
//    - using a pointer to something that was deallocated.
//    - using an uninitialized hence bogus pointer.
//    - using a null pointer.
//    - overflowing a buffer.
// 2. A segfault is accessing memory that you're `not allowed to access`. It's
// read-only, you don't have permission, etc...

#include <iostream>
#include <stdlib.h>
#include <unistd.h>

void double_free() {
  int *malloc_test = (int *)malloc(100000);
  std::cout << (void *)&malloc_test
            << std::endl; // malloc_test point is on stack
  std::cout << &(*malloc_test)
            << std::endl; // malloc_test data address is on heap
  free(malloc_test);
  std::cout << (void *)&malloc_test
            << std::endl; // malloc_test point is on stack
  free(malloc_test);
}

void use_not_init_ptr() {
  // int *test = nullptr;
  int *test; // test address segment is not allowed write
  // sleep(30); // for check /proc/pid/maps
  std::cout << (void *)test << std::endl;
  std::cout << *test << std::endl; // can read sometimes
  *test = 1;                       // not allowed write
}

int main(int argc, char *argv[]) {
  // double_free(); // double free or corruption (!prev)

  use_not_init_ptr(); // Segmentation fault

  return 0;
}
