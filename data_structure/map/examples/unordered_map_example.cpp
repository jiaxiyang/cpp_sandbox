#include <iostream>
#include <string>
#include <unordered_map>

void print_map(std::unordered_map<std::string, std::string> &u) {
  // 迭代并打印 unordered_map 的关键和值
  for (const auto &n : u) {
    std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
  }

  std::cout << std::endl;
}

int main() {
  // 创建三个 string 的 unordered_map （映射到 string ）
  std::unordered_map<std::string, std::string> u = {
      {"RED", "#FF0000"}, {"GREEN", "#00FF00"}, {"BLUE", "#0000FF"}};
  print_map(u);

  // 添加新入口到 unordered_map
  u["BLACK"] = "#000001";
  u["BLACK"] = "#000000";
  u["WHITE"] = "#FFFFFF";
  print_map(u);
  std::cout << "size: " << u.size() << std::endl;

  // 用关键字输出值
  std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n\n";

  // 查找
  auto it = u.find("GRAY"); // 不会增加 unordered_map size
  if (it == u.end()) {
    std::cout << "Can't find GRAY in container" << std::endl;
  }
  std::cout << "size: " << u.size() << std::endl;
  std::cout << u["GRAY"] << std::endl; // 会增加 unordered_map size
  std::cout << "size: " << u.size() << std::endl;

  it = u.find("GRAY");
  if (it == u.end()) {
    std::cout << "Can't find GRAY in container" << std::endl;
  }

  // misc
  std::cout << "size: " << u.size() << std::endl;
  std::cout << "max size: " << u.max_size() << std::endl;

  return 0;
}
