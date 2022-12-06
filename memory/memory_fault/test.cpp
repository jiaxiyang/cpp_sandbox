// 1. Segmentation faults occur when accessing memory which does not belong to
// your process. They are very common and are typically the result of:
//    - using a pointer to something that was deallocated.
//    - using an uninitialized hence bogus pointer.
//    - using a null pointer.
//    - overflowing a buffer.
// 2. A segfault is accessing memory that you're `not allowed to access`. It's
// read-only, you don't have permission, etc...

#include <array>
#include <cstdlib>
#include <iostream>
// #include <stdlib.h>
#include <unistd.h>
#include <vector>

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

void use_after_free() {
  int *malloc_test = (int *)malloc(100000);
  malloc_test[100] = 100;
  std::cout << (void *)&malloc_test
            << std::endl; // malloc_test point is on stack
  std::cout << &(*malloc_test)
            << std::endl; // malloc_test data address is on heap
  free(malloc_test);
  std::cout << (void *)&malloc_test << std::endl;
  std::cout << malloc_test[100] << std::endl;
  malloc_test = nullptr; // pointer should be nullptr after free
  std::cout << (void *)&malloc_test << std::endl;
  std::cout << malloc_test[100] << std::endl;
}

void use_null_ptr() {
  int *test = nullptr;
  std::cout << (void *)test << std::endl;
  std::cout << *test << std::endl; // not allow read addre 0x0
}

void use_not_init_ptr() {
  // int *test = nullptr;
  int *test; // test address segment is not allowed write
  // sleep(30); // for check /proc/pid/maps
  std::cout << (void *)test << std::endl;
  std::cout << *test << std::endl; // can read sometimes
  *test = 1;                       // not allowed write
}

void overflow_buf_vec() {
  // std::vector<int> vec(10, 1);
  std::vector<int> vec;
  vec.push_back(2);

  std::cout << (void *)&vec[0] << std::endl;
  std::cout << (void *)&vec[10] << std::endl;
  std::cout << vec[10] << std::endl; // []操作符不进行越界检查
  std::cout << vec.size() << std::endl;
  std::cout << vec.capacity() << std::endl;
  vec[11] = 100;
  vec.at(0) = 22222;
  std::cout << vec.at(0) << std::endl;
  std::cout << vec.at(10) << std::endl; // at进行越界检查
}

void overflow_buf_array_cpp() {
  // std::vector<int> vec(10, 1);
  std::array<int, 10> vec{1};
  // vec.push_back(2);

  std::cout << (void *)&vec[0] << std::endl;
  std::cout << (void *)&vec[10] << std::endl;
  std::cout << vec[10] << std::endl; // []操作符不进行越界检查
  std::cout << vec.size() << std::endl;
  vec[11] = 100;
  vec.at(0) = 22222;
  std::cout << vec.at(0) << std::endl;
  std::cout << vec.at(10) << std::endl; // at进行越界检查
}

void overflow_buf_array_c() {
  // std::vector<int> vec(10, 1);
  int vec[10] = {1}; // 栈上
  // int vec1[100] = {1}; // 栈上

  std::cout << (void *)&vec[0] << std::endl;
  std::cout << (void *)&vec[10] << std::endl;
  std::cout << vec[0] << std::endl;
  std::cout << vec[10] << std::endl; // []操作符不进行越界检查
  vec[10] = 100;                     //不一定出错，加vec1不出错
}

void buf_not_init() {
  std::vector<int> vec;
  vec.reserve(10);
  std::cout << vec.size() << std::endl;
  std::cout << vec[0] << std::endl;
}

void bus_error() {
  std::cout << "bus error" << std::endl;
#if defined(__GNUC__)
#if defined(__i386__)
  /* Enable Alignment Checking on x86 */
  __asm__("pushf\norl $0x40000,(%esp)\npopf");
#elif defined(__x86_64__)
  /* Enable Alignment Checking on x86_64 */
  __asm__("pushf\norl $0x40000,(%rsp)\npopf");
#endif
#endif

  char c[11] = "xxx";
  std::cout << (void *)&c[0] << std::endl;
  std::cout << (void *)&c[5] << std::endl;
  std::cout << *((int *)&c[5]) << std::endl;
}

void memory_error() {

  double_free(); // double free or corruption (!prev)

  // use_after_free(); // Segmentation fault

  // use_null_ptr(); // Segmentation fault

  // use_not_init_ptr(); // Segmentation fault

  // bus_error(); // Bus error

  // overflow_buf_vec(); // throwing an instance of 'std::out_of_range'

  // overflow_buf_array_cpp(); // throwing an instance of 'std::out_of_range'

  // overflow_buf_array_c(); // stack smashing detected

  // buf_not_init();
}

void memory_leak() { int *test = new int[1]; }

int main(int argc, char *argv[]) {
  memory_error();
  memory_leak();
  return 0;
}
