#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
std::string pg_version(std::string so_name) {
  typedef char *(*CAC_FUNC)();
  CAC_FUNC cac_func = NULL;
  auto handle = dlopen(so_name.c_str(), RTLD_LAZY);
  if (!handle) {
    auto ret = dlclose(handle);
    return std::string("Can't open " + so_name);
  }

  dlerror();

  cac_func = (CAC_FUNC)dlsym(handle, "pg_version_verbose");
  if (!cac_func) {
    auto ret = dlclose(handle);
    return std::string("No version symbol in " + so_name);
  }

  auto ret = std::string(cac_func());
  auto ret_close = dlclose(handle);
  return ret;
}

int main(int argc, char *argv[]) {
  for (auto i = 1u; i < argc; ++i) {
    std::cout << "********************* " << argv[i] << " *********************"
              << std::endl;
    std::cout << pg_version(argv[i]) << std::endl << std::endl;
  }
}
