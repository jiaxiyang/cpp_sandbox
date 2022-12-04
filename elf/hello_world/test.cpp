
// #include <unistd.h>
// #include <iostream>
int get() { return 1; }

static int a = 0;
int in_bigvar_bss[16300];
int bigvar_in_data[16300] = {1};
int var_in_data[5] = {1, 2, 3, 4, 5};
int main(int argc, char *argv[]) {
  // int *test = new int[10000];
  // delete[] test;
  // while (true) {
  //   sleep(1);
  // }
  a = 2;

  return 0;
}
