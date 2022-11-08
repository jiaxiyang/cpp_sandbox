#include <glog/logging.h>
#include <singleton.hpp>

// int Singleton::single_static = 1;

Singleton &Singleton::Instance() {
  static Singleton singleton;
  LOG(INFO) << "singleton address: " << (void *)&singleton;
  // LOG(INFO) << "singleton varible address: " << (void *)&single_static;
  return singleton;
}
static auto testxxx = Singleton::Instance();
