#pragma once
#include <animal.hpp>

class Dog : public Animal {
public:
  Dog() = default;
  ~Dog() = default;

  std::string GetName() override;
  static int hold_ __attribute__((used));
};
