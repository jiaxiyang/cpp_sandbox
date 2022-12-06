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
