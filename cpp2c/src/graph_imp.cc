#include "graph_imp.h"
#include <glog/logging.h>

GraphImp::GraphImp() { LOG(INFO) << "Construction of GraphImp"; }

GraphImp::~GraphImp() { LOG(INFO) << "Deconstruction of GraphImp"; }

void GraphImp::Feed(const std::string &input_name) {
  LOG(INFO) << "Feed................";
}
