#include <dlfcn.h>
#include <glog/logging.h>
#include <stdlib.h>
#include <string>
#include <vector>
std::vector<std::string> pg_version(std::vector<std::string> so_names) {
  typedef char *(*CAC_FUNC)();
  CAC_FUNC cac_func = NULL;
  std::vector<std::string> version_list;
  for (auto so : so_names) {
    LOG(INFO) << "so=" << so;
    auto handle = dlopen(so.c_str(), RTLD_LAZY);
    if (!handle) {
      LOG(INFO) << "Can't open " << so;
      version_list.push_back(dlerror());
      continue;
    }

    dlerror();

    cac_func = (CAC_FUNC)dlsym(handle, "pg_version_verbose");
    if (!cac_func) {
      version_list.push_back(dlerror());
      continue;
    }

    version_list.push_back(cac_func());
    dlclose(handle);
  }
  return version_list;
}

int main(int argc, char *argv[]) {

  std::vector<std::string> so_list = {"build/libversion.so",
                                      "build/component1/libversion1.so"};
  auto so_res = pg_version(so_list);
  LOG(INFO) << "so_res.size()=" << so_res.size();
  for (auto &str : so_res) {
    LOG(INFO) << "version=" << str;
  }
}
