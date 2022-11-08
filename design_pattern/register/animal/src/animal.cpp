#include "animal.hpp"
#include <glog/logging.h>

std::unordered_map<std::string, std::function<std::unique_ptr<Animal>()>>
    AnimalRegister::map_;

std::unique_ptr<Animal> AnimalRegister::Create(std::string name) {
  if (map_.find(name) != map_.end()) {
    auto &creator = map_[name];
    return creator();
  } else {
    LOG(INFO) << "Can't create name=" << name;
    return nullptr;
  }
}

int AnimalRegister::Regist(std::string name,
                           std::function<std::unique_ptr<Animal>()> func) {
  LOG(INFO) << "..............regist name=" << name;
  map_[name] = func;
  return 0;
}
