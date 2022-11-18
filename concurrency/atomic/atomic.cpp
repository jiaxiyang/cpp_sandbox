#include <atomic>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

// 互斥量的加锁一般是针对一个代码段，而原子操作针对的一般都是一个变量。
// atomic 不一定免锁

std::atomic<int> i = 0;
// int i = 0;

void test() {
  std::cout << "i = " << i.load() << std::endl;
  for (auto j = 0u; j < 10000; ++j) {
    // i.store(i.load() + 1); //有问题 i.load()之后变化了 store也会变化
    i++;
  }
}

int main(int argc, char *argv[]) {
  std::vector<int> results(10);
  std::vector<std::thread> threads;
  threads.reserve(results.size());
  for (auto i = 0u; i < results.size(); ++i) {
    threads.emplace_back(std::thread(test));
  }

  for (auto &t : threads) {
    t.join();
  }

  // 100000 is right
  std::cout << "i = " << i << std::endl;

  return 0;
}

// test lock free
struct A {
  int a[100];
};
struct B {
  int x, y;
};

int main1(int argc, char *argv[]) {
  std::cout << std::boolalpha << "std::atomic<A> is lock free? "
            << std::atomic<A>{}.is_lock_free() << '\n'
            << "std::atomic<B> is lock free? "
            << std::atomic<B>{}.is_lock_free() << '\n';
  return 0;
}
