#include <iostream>
#include <set>
#include <vector>

void print_set(std::set<int> &s) {
  for (int n : s) {
    std::cout << n << ' ';
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  // init
  std::set<int> a; // 定义一个int类型的集合a
                   // set<int> a(10); // error，未定义这种构造函数
                   // set<int> a(10, 1); // error，未定义这种构造函数
  std::set<int> b(a);                  // 定义并用集合a初始化集合b
  std::set<int> c(a.begin(), a.end()); //
  print_set(c);

  std::vector<int> vec{1, 2, 2, 3, 4, 7};
  std::set<int> d(vec.begin(), vec.begin() + 4);
  std::cout << "size: " << d.size() << std::endl;
  print_set(d);

  // count
  std::cout << "count 2: " << d.count(2) << std::endl;
  std::cout << "count 10: " << d.count(10) << std::endl;

  // add
  d.insert(11);
  d.emplace(9);
  print_set(d);

  // delete item
  d.erase(2);
  print_set(d);

  // find
  auto it = d.find(20);
  if (it == d.end()) {
    std::cout << "Cann't find 20" << std::endl;
  }

  it = d.find(1);
  if (it != d.end()) {
    std::cout << "Find 1" << std::endl;
  }

  auto count = d.count(20);
  if (count == 0) {
    std::cout << "Cann't find 20" << std::endl;
  }

  count = d.count(1);
  if (count != 0) {
    std::cout << "Find 1" << std::endl;
  }

  return 0;
}
