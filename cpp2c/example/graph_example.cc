#include <graph.h>

int main(int argc, char *argv[]) {
  {
    auto graph = Graph::CreateGraphFromJson("Json String");
    graph->Feed("feed");
  }

  {
    auto graph = Graph::CreateGraphFromJsonFile("Json File");
    graph->Feed("feed");
  }

  return 0;
}
