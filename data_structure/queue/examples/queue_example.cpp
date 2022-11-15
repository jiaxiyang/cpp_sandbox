#include <iostream>
#include <queue>

void print_queue(std::queue<int> q) {
  std::string str;
  while (!q.empty()) {
    str = " " + std::to_string(q.front()) + str;
    q.pop();
    if (!q.empty()) {
      str = " ->" + str;
    }
  }
  std::cout << str << std::endl;
}

int main(int argc, char *argv[]) {
  std::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(4);
  q.emplace(5);
  print_queue(q);

  q.pop();
  print_queue(q);

  // misc
  std::cout << "size: " << q.size() << std::endl;
  std::cout << "back: " << q.back() << std::endl;

  return 0;
}
