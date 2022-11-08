#pragma once
#include <iostream>

class Singleton {
public:
  ~Singleton() = default;

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
