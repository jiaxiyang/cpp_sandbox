// links
// https://www.softwaretestinghelp.com/graph-implementation-cpp/

#include <iostream>
using namespace std;

// stores adjacency list items
struct Vertex {
  int val;
  int cost;
  Vertex *next;
};

// structure to store edges
struct Edge {
  int start;
  int end;
  int weight;
};

class Graph {
  // insert new nodes into adjacency list from given graph
  Vertex *getAdjListNode(int value, int weight, Vertex *head) {
    Vertex *newNode = new Vertex;
    newNode->val = value;
    newNode->cost = weight;

    newNode->next = head; // point new node to current head
    return newNode;
  }
  int N; // number of nodes in the graph
public:
  Vertex **head; // adjacency list as array of pointers
  // Constructor
  Graph(Edge edges[], int n, int N) {
    // allocate new node
    head = new Vertex *[N]();
    this->N = N;
    // initialize head pointer for all vertices
    for (int i = 0; i < N; ++i)
      head[i] = nullptr;
    // construct directed graph by adding edges to it
    for (unsigned i = 0; i < n; i++) {
      int start = edges[i].start;
      int end = edges[i].end;
      int weight = edges[i].weight;
      // insert in the beginning
      Vertex *newNode = getAdjListNode(end, weight, head[start]);

      // point head pointer to new node
      head[start] = newNode;
    }
  }

  // Destructor
  ~Graph() {
    for (int i = 0; i < N; i++)
      delete[] head[i];
    delete[] head;
  }
};

// print all adjacent vertices of given vertex
void display_AdjList(Vertex *ptr, int i) {
  while (ptr != nullptr) {
    cout << "(" << i << ", " << ptr->val << ", " << ptr->cost << ") ";
    // cout << "(" << i << ", " << ptr->val << ") ";
    ptr = ptr->next;
  }
  cout << endl;
}

// graph implementation
int main() {
  // graph edges array.
  Edge edges[] = {// (x, y, w) -> edge from x to y with weight w
                  {0, 1, 2}, {0, 2, 4}, {1, 4, 3},
                  {2, 3, 2}, {3, 1, 4}, {4, 3, 3}};
  int N = 5; // Number of vertices in the graph
  cout << "N " << N << endl;

  // calculate number of edges
  int n = sizeof(edges) / sizeof(edges[0]);
  cout << "n " << n << endl;

  // construct graph
  Graph graph(edges, n, N);
  // print adjacency list representation of graph
  cout << "Graph adjacency list " << endl
       << "(start_vertex, end_vertex, weight):" << endl;
  for (int i = 0; i < N; i++) {
    // display adjacent vertices of vertex i
    display_AdjList(graph.head[i], i);
  }
  return 0;
}
