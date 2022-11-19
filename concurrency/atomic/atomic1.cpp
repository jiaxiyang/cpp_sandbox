#include <atomic>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

int main(int argc, char *argv[]) {
  auto constexpr num = 100;
  std::vector<std::thread> vecThread(num);
  int i{};
  // std::atomic<int> i{};

  for (auto &t : vecThread) {
    t = std::thread([&i] {
      for (int n = 0; n < num; ++n)
        std::cout << ++i << " ";
    });
  }

  for (auto &t : vecThread) {
    t.join();
  }
  std::cout << "num * num : " << num * num << std::endl;
  std::cout << "i: " << i << std::endl;
  std::cout << "num * num - i : " << num * num - i << std::endl;
  return 0;
}
