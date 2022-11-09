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
    // return std::string("Can't open " + so_name);
    return "";
  }

  dlerror();

  cac_func = (CAC_FUNC)dlsym(handle, "pg_version_verbose");
  if (!cac_func) {
    auto ret = dlclose(handle);
    // return std::string("No version symbol in " + so_name);
    return "";
  }

  auto ret = std::string(cac_func());
  auto ret_close = dlclose(handle);
  return ret;
}

extern "C" const char *pg_version_verbose();

int main(int argc, char *argv[]) {
  if (argc < 1 || std::string(argv[1]).compare("-h") == 0 ||
      std::string(argv[1]).compare("--help") == 0) {
    std::cout << "\nUsage:\n"
              << "\t1. Check share libraries version\n"
              << "\t\t" << argv[0] << " so1 so2 ...\n"
              << "\n\t2. Check linked share libraries version of elf\n"
              << "\t\tldd elf | grep \"=> .\" | awk '{print $3}' | xargs "
              << argv[0] << std::endl
              << std::endl;
    return 0;
  }

  // print tool version
  auto info = std::string(pg_version_verbose());
  if (info != "") {
    std::cout << "********************* " << argv[0] << " *********************"
              << std::endl;
    std::cout << info << std::endl << std::endl;
  }

  // print lib version
  for (auto i = 1u; i < argc; ++i) {
    auto info = pg_version(argv[i]);
    if (info != "") {
      std::cout << "********************* " << argv[i]
                << " *********************" << std::endl;
      std::cout << info << std::endl << std::endl;
    }
  }
}
