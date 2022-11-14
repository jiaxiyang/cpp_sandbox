#include <iostream>
#include <stack>

void print_stack(std::stack<int> s) {
  while (!s.empty()) {
    std::cout << s.top() << " ";
    s.pop();
    if (!s.empty())
      std::cout << "<- ";
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  std::stack<int> s;
  s.push(1);
  s.push(3);
  s.push(2);
  s.emplace(4);

  print_stack(s);

  std::cout << "top: " << s.top() << std::endl;
  std::cout << "size: " << s.size() << std::endl;
  s.pop(); // 删除栈顶值， 不返回
  print_stack(s);

  return 0;
}
