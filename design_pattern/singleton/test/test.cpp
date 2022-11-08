#include <glog/logging.h>
#include <iostream>

#include <singleton.hpp>
extern int test_flag;

int main(int argc, char *argv[]) {
  LOG(INFO) << "test_flag=" << test_flag;
  Singleton::Instance();

  return 0;
}
