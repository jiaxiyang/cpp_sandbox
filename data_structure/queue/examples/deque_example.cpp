#include <deque>
#include <iostream>

void print_deque(std::deque<int> q) {
  std::string str;
  while (!q.empty()) {
    str = " " + std::to_string(q.front()) + str;
    q.pop_front();
    if (!q.empty()) {
      str = " ->" + str;
    }
  }
  std::cout << str << std::endl;
}

int main(int argc, char *argv[]) {
  std::deque<int> q;
  q.push_back(1);
  q.push_back(2);
  q.push_back(4);
  q.push_front(6);
  q.emplace_back(5);
  q.emplace_front(8);
  print_deque(q);

  q.pop_front();
  q.pop_back();
  print_deque(q);

  q.erase(q.begin());
  print_deque(q);

  q.erase(q.end());
  print_deque(q);

  // misc
  std::cout << "size: " << q.size() << std::endl;
  std::cout << "max_size: " << q.max_size() << std::endl;
  std::cout << "back: " << q.back() << std::endl;

  return 0;
}
