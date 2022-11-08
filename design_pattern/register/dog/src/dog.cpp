#include "dog.hpp"

std::string Dog::GetName() { return "Dog"; };
// #pragma optimize off
ANIMALREGIST(Dog);
// #pragma optimize on
// int dog_test = Dog::hold_;
// extern int test_xxxx();
// int test_xxxx() { return dog_test; }
// #pragma comment(linker, "/export:dog_test")
// auto ret = AnimalRegister::Instance().Regist(
//     "Dog", []() -> std::unique_ptr<Animal> { return std::make_unique<Dog>();
//     });
// //
