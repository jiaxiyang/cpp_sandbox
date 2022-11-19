#include <algorithm>
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

  // find
  auto it = std::find(q.begin(), q.end(), 3);
  if (it != q.end()) {
    std::cout << *it << std::endl;
  } else {
    std::cout << "Can't find" << std::endl;
  }

  // find if
  auto is_large_than_1 = [](int i) { return i > 1; };
  it = std::find_if(q.begin(), q.end(), is_large_than_1);
  if (it != q.end()) {
    std::cout << *it << std::endl;
  } else {
    std::cout << "Can't find" << std::endl;
  }

  // misc
  std::cout << "size: " << q.size() << std::endl;
  std::cout << "max_size: " << q.max_size() << std::endl;
  std::cout << "back: " << q.back() << std::endl;

  return 0;
}
