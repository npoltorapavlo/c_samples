#include "dynamicloader.h"

#include "sharedlibrary.h"

#include <chrono>
#include <thread>

int main(int argc, char** argv) {

  {
    DynamicLoader loader(
#ifdef __APPLE__
        "sharedlibrary/libsharedlibrary.dylib"
#else
        "sharedlibrary/libsharedlibrary.so"
#endif
    );

    loader.open();

    void (*create)(std::shared_ptr<ISharedLibraryImp>&);
    create = reinterpret_cast<void (*)(std::shared_ptr<ISharedLibraryImp>&)> (loader.lookup("create"));
    std::shared_ptr<ISharedLibraryImp> imp;
    create(imp);
    imp->startThread();
  }


  std::this_thread::sleep_for(std::chrono::seconds(5));

  return 0;
}