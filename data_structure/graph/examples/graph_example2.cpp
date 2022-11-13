#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct vertex {
  typedef pair<int, vertex *> ve;
  vector<ve> adj; // cost of edge, destination vertex
  string name;
  vertex(string s) : name(s) {}
};

class Graph {
public:
  typedef map<string, vertex *> vmap;
  vmap work;
  void addvertex(const string &);
  void addedge(const string &from, const string &to, double cost);
};

void Graph::addvertex(const string &name) {
  vmap::iterator itr = work.find(name);
  if (itr == work.end()) {
    vertex *v;
    v = new vertex(name);
    work[name] = v;
    return;
  }
  cout << "\nVertex already exists!";
}

void Graph::addedge(const string &from, const string &to, double cost) {
  vertex *f = (work.find(from)->second);
  vertex *t = (work.find(to)->second);
  pair<int, vertex *> edge = make_pair(cost, t);
  f->adj.push_back(edge);
}

int main(int argc, char *argv[]) {
  Graph g;
  g.addvertex("vertex1");
  g.addvertex("vertex1");
  g.addvertex("vertex2");
  g.addedge("vertex1", "vertex2", 1.11);

  return 0;
}
