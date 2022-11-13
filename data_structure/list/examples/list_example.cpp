#include <algorithm>
#include <iostream>
#include <list>

void print_list(std::list<int> &l) {
  for (int n : l) {
    std::cout << n << ' ';
  }
  std::cout << std::endl;
}

int main() {
  // Create a list containing integers
  std::list<int> l = {7, 5, 16, 8};
  print_list(l);

  // Add an integer to the front of the list
  l.push_front(25);
  // Add an integer to the back of the list
  l.push_back(13);

  // Insert an integer before 16 by searching
  auto it = std::find(l.begin(), l.end(), 16);
  if (it != l.end()) {
    l.insert(it, 42);
  }

  // Iterate and print values of the list
  print_list(l);

  l.pop_back();
  l.pop_front();
  print_list(l);

  // get first item
  std::cout << "front: " << l.front() << std::endl;

  // get back item
  std::cout << "back: " << l.back() << std::endl;

  // get next item
  std::cout << "next: " << *std::next(it, 1) << std::endl;

  // ascending sort
  l.sort();
  print_list(l);

  // descending sort
  l.sort(std::greater<int>());
  print_list(l);

  // unique
  l.push_back(5);
  print_list(l);

  l.unique();
  print_list(l);
}
