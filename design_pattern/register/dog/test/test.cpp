#include "dog.hpp"
#include <glog/logging.h>

// ANIMALREGIST(Dog);
int main(int argc, char *argv[]) {
  LOG(INFO) << "dog test...........";
  LOG(INFO) << "Dog::hold_=" << Dog::hold_;
  auto dog = AnimalRegister::Create("Dog");
  LOG(INFO) << "dog name: " << dog->GetName();
  return 0;
}
