
#include <iostream>
#include <memory>

class Test {
public:
  Test() {
    public_ = 1;
    private_ = 1;
  }

  ~Test() {}

public:
  int public_;

private:
  int private_;
};

int test_function1() {
  auto test = std::make_shared<Test>();
  int a = 1;
  float b = 1.0;
  std::cout << a << b;

  return a;
}

int test_function() {
  test_function1();
  int a = 1;
  float b = 1.0;
  std::cout << a << b;
  return a;
}

int main(int argc, char *argv[]) {
  test_function();
  test_function1();

  return 0;
}
