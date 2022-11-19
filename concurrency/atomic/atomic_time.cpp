#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>
using Clock = std::chrono::steady_clock;

#define __TIC__(tag) auto __##tag##_start_time = Clock::now();

#define __TOC__(tag)                                                           \
  auto __##tag##_end_time = Clock::now();                                      \
  std::cout << #tag << " : "                                                   \
            << std::chrono::duration_cast<std::chrono::microseconds>(          \
                   __##tag##_end_time - __##tag##_start_time)                  \
                   .count()                                                    \
            << "us" << std::endl;

auto constexpr num = 2000;

void atomic() {
  std::vector<std::thread> vecThread(num);
  // int i{};
  std::atomic<int> i{};

  __TIC__(ATOMIC)
  for (auto &t : vecThread) {
    t = std::thread([&i] {
      for (int n = 0; n < num; ++n) {
        // std::cout << ++i << " ";
        ++i;
      }
    });
  }
  for (auto &t : vecThread) {
    t.join();
  }
  __TOC__(ATOMIC)

  // std::cout << "num * num : " << num * num << std::endl;
  // std::cout << "i: " << i << std::endl;
  std::cout << "num * num - i : " << num * num - i << std::endl;
}

void mutex() {
  std::vector<std::thread> vecThread(num);
  int i{};
  // std::atomic<int> i{};
  std::mutex mut;

  __TIC__(MUTEX)
  for (auto &t : vecThread) {
    t = std::thread([&i, &mut] {
      for (int n = 0; n < num; ++n) {

        std::lock_guard<std::mutex> lock(mut);
        // std::cout << ++i << " ";
        ++i;
      }
    });
  }

  for (auto &t : vecThread) {
    t.join();
  }
  __TOC__(MUTEX)

  // std::cout << "num * num : " << num * num << std::endl;
  // std::cout << "i: " << i << std::endl;
  std::cout << "num * num - i : " << num * num - i << std::endl;
}

int main(int argc, char *argv[]) {
  atomic();
  atomic(); // 65ms
  mutex();  // 380ms

  return 0;
}
