#include "dog.hpp"
// #include "dog1.hpp"
#include <dlfcn.h>
#include <glog/logging.h>
extern int dog_test;
// int test_xxxx() { return dog_test; }
// inline void test_function(){};
// ANIMALREGIST(Dog);
int main(int argc, char *argv[]) {
  LOG(INFO) << "dog test1...........";
  // sleep(100);

  // LOG(INFO) << "dog_test=" << dog_test;
  // void *handle;
  // handle = dlopen("libdog.so", RTLD_LAZY);
  // dlclose(handle);

  auto dog = AnimalRegister::Create("Dog");
  LOG(INFO) << "dog name: " << dog->GetName();

  return 0;
}
// 动态加载libdog, 看看能否注册进去
