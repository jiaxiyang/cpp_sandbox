#include <dlfcn.h>
#include <glog/logging.h>
#include <graph.h>

typedef void *(*CREATE_GRAPH)(char *);
typedef void (*RELEASE_GRAPH)(void *);
int main(int argc, char *argv[]) {
  LOG(INFO) << "*************** dlopen example *****************";

  void *graph_handle;
  graph_handle = dlopen("libgraph.so", RTLD_LAZY);
  if (!graph_handle) {
    LOG(ERROR) << "Can't find libgraph.so";
    exit(EXIT_FAILURE);
  }

  dlerror();
  CREATE_GRAPH create_graph = nullptr;
  create_graph = (CREATE_GRAPH)dlsym(graph_handle, "CreateGraphFromJsonFile");
  RELEASE_GRAPH release_graph = nullptr;
  release_graph = (RELEASE_GRAPH)dlsym(graph_handle, "ReleaseGraph");
  char *error = dlerror();
  if (error != NULL) {
    LOG(ERROR) << "Can't find symbol in  libgraph.so";
    exit(EXIT_FAILURE);
  }

  std::string str{"Json File"};
  auto graph_struct_ptr_c = (*create_graph)(const_cast<char *>(str.c_str()));
  auto graph_struct_ptr = static_cast<GraphStruct *>(graph_struct_ptr_c);
  graph_struct_ptr->graph_->Feed("dlopen feed");
  (*release_graph)(graph_struct_ptr_c);

  dlclose(graph_handle);

  return 0;
}
