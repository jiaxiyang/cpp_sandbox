#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

// #define ANIMALREGIST(name)                                                     \
//   int name::hold_ = AnimalRegister::Instance().Regist(                         \
//       #name,                                                                   \
//       []() -> std::unique_ptr<Animal> { return std::make_unique<name>(); });
#define ANIMALREGIST(name)                                                     \
  int name::hold_ = AnimalRegister::Instance().Regist(                         \
      #name,                                                                   \
      []() -> std::unique_ptr<Animal> { return std::make_unique<name>(); });

class Animal {

public:
  virtual std::string GetName() = 0;
};

class AnimalRegister {

public:
  AnimalRegister() = default;
  ~AnimalRegister() = default;
  void name(){};

public:
  static AnimalRegister &Instance() {
    static AnimalRegister ar;
    return ar;
  }

  static std::unique_ptr<Animal> Create(std::string name);
  int Regist(std::string name, std::function<std::unique_ptr<Animal>()> fun);

private:
  static std::unordered_map<std::string,
                            std::function<std::unique_ptr<Animal>()>>
      map_;
};
