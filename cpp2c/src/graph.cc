#include "graph.h"
#include "graph_imp.h"
#include <glog/logging.h>

std::shared_ptr<Graph> Graph::CreateGraphFromJson(const std::string &json_str) {
  LOG(INFO) << "json_str=" << json_str;
  return std::make_shared<GraphImp>();
}

std::shared_ptr<Graph>
Graph::CreateGraphFromJsonFile(const std::string &json_file) {
  LOG(INFO) << "json_file=" << json_file;
  return std::make_shared<GraphImp>();
}

extern "C" {

// shared_ptr 两种解决方法(堆上手动管理智能指针，栈由系统自动管理)
// 1. struct存graph
// 2. 创建share_ptr的指针，指针不释放 (不适合此场景，已经创建栈上的shared_ptr,
// 没法调用new)

void *CreateGraphFromJson(char *json_str) {
  auto graph_struct = new GraphStruct;
  graph_struct->graph_ = Graph::CreateGraphFromJson(std::string(json_str));
  LOG(INFO) << "CreateGraphFromJson";
  return static_cast<void *>(graph_struct);
}

void *CreateGraphFromJsonFile(char *json_file) {
  auto graph_struct = new GraphStruct;
  graph_struct->graph_ = Graph::CreateGraphFromJsonFile(std::string(json_file));
  return static_cast<void *>(graph_struct);
}

void ReleaseGraph(void *self) {
  auto ret = static_cast<GraphStruct *>(self);
  LOG(INFO) << "Release Graph";
  delete ret;
}
}
