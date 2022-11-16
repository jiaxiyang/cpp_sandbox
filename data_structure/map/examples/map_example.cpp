#include <iostream>
#include <map>
#include <string>
// 与 unordered_map 用法一样
// void print_map(std::map<std::string, std::string> &m) {
//   // 迭代并打印 map 的关键和值
//   for (const auto &n : m) {
//     std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
//   }

//   std::cout << std::endl;
// }

void print_map(std::map<std::string, std::string> &m) {
  // 迭代并打印 map 的关键和值
  for (const auto &[key, value] : m) {
    std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
  }

  std::cout << std::endl;
}

int main() {
  // 创建三个 string 的 map （映射到 string ）
  std::map<std::string, std::string> m = {
      {"RED", "#FF0000"}, {"GREEN", "#00FF00"}, {"BLUE", "#0000FF"}};
  print_map(m);

  // 添加新入口到 map
  m["BLACK"] = "#000001";
  m["BLACK"] = "#000000";
  m["WHITE"] = "#FFFFFF";
  print_map(m);
  std::cout << "size: " << m.size() << std::endl;

  // 用关键字输出值
  std::cout << "The HEX of color RED is:[" << m["RED"] << "]\n\n";

  // 查找
  auto it = m.find("GRAY"); // 不会增加 map size
  if (it == m.end()) {
    std::cout << "Can't find GRAY in container" << std::endl;
  }
  std::cout << "size: " << m.size() << std::endl;
  std::cout << m["GRAY"] << std::endl; // 会增加 map size
  std::cout << "size: " << m.size() << std::endl;

  it = m.find("GRAY");
  if (it == m.end()) {
    std::cout << "Can't find GRAY in container" << std::endl;
  }

  // misc
  std::cout << "size: " << m.size() << std::endl;
  std::cout << "max size: " << m.max_size() << std::endl;

  return 0;
}
