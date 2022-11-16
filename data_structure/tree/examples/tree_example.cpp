#include <iostream>
#include <vector>
// link: https://stackoverflow.com/a/15473485
template <typename T> struct tree_node {
  T value;
  std::vector<tree_node<T> *> children;
  void walk_depth_first() const;
  void walk_depth_last() const;
};

template <typename T> void tree_node<T>::walk_depth_first() const {
  std::cout << value << " ";
  for (auto &n : children)
    n->walk_depth_first();
}

template <typename T> void tree_node<T>::walk_depth_last() const {
  for (auto &n : children)
    n->walk_depth_last();
  std::cout << value << " ";
}

int main(int argc, char *argv[]) {
  //     1
  //   2   3
  // 4
  tree_node<int> n1;
  n1.value = 1;

  tree_node<int> n2;
  n2.value = 2;

  tree_node<int> n3;
  n3.value = 3;

  tree_node<int> n4;
  n4.value = 4;

  n1.children.push_back(&n2);
  n1.children.push_back(&n3);
  n2.children.push_back(&n4);

  n1.walk_depth_first();
  std::cout << std::endl;
  n1.walk_depth_last();

  return 0;
}
