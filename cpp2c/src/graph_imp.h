#pragma once
#include "graph.h"

class GraphImp : public Graph {
public:
  GraphImp();
  ~GraphImp();
  void Feed(const std::string &input_name) override;
};
