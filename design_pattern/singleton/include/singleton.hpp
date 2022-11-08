#pragma once
#include <iostream>

class Singleton {
public:
  ~Singleton() = default;

  // static __attribute__((visibility("default"))) Singleton &Instance();
  // //暴露函数符号
  static Singleton &Instance();

  // static Singleton &Instance() {
  //   static Singleton singleton;
  //   std::cout << "singleton address: " << (void *)&singleton << std::endl;
  //   return singleton;
  // }

private:
  Singleton() = default;
  // static int single_static;
};
