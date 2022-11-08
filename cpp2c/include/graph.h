#pragma once
#include <memory>
#include <string>
#include <vector>

class Graph {
public:
  virtual ~Graph() = default;
  virtual void Feed(const std::string &input_name) = 0;

  static std::shared_ptr<Graph>
  CreateGraphFromJson(const std::string &json_str);

  static std::shared_ptr<Graph>
  CreateGraphFromJsonFile(const std::string &json_file);
};

struct GraphStruct {
  std::shared_ptr<Graph> graph_;
};

extern "C" {
void *CreateGraphFromJson(char *json_str);
void *CreateGraphFromJsonFile(char *json_file);
void ReleaseGraph(void *);
}
