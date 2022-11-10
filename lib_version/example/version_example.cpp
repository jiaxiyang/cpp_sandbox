#include <dlfcn.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

extern "C" const char *pg_version_verbose();
extern int test_version;
extern int test_version1;
void print_something2() {
  std::cout << test_version << std::endl;
  std::cout << test_version1 << std::endl;
}

std::string pg_version(std::string so_name) {
  typedef char *(*CAC_FUNC)();
  CAC_FUNC cac_func = NULL;
  auto handle = dlopen(so_name.c_str(), RTLD_LAZY);
  if (!handle) {
    return std::string("Can't open " + so_name);
  }

  dlerror();

  cac_func = (CAC_FUNC)dlsym(handle, "pg_version_verbose");

  if (!cac_func) {
    dlclose(handle);
    return std::string("No version symbol in " + so_name);
  }

  std::cout << so_name << " pg_version_verbose address: " << (void *)cac_func
            << std::endl;

  auto ret = std::string(cac_func());
  auto ret_close = dlclose(handle);
  return ret;
}

int main(int argc, char *argv[]) {
  std::cout << "********************* " << argv[0] << " *********************"
            << std::endl;
  std::cout << argv[0]
            << " pg_version_verbose address: " << (void *)pg_version_verbose
            << std::endl;

  std::cout << pg_version_verbose() << std::endl;

  std::cout
      << "\n********************* build/libversion.so *********************"
      << std::endl;
  std::cout << "version=" << pg_version("build/libversion.so") << std::endl;

  std::cout << "\n********************* build/component1/libversion1.so "
               "*********************"
            << std::endl;
  std::cout << "version1=" << pg_version("build/component1/libversion1.so")
            << std::endl;
}
