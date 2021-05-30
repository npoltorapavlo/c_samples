#include "dynloader.h"

#include <dlfcn.h>

DynLoader::DynLoader(const char* filename)
 : _filename(filename)
 , _handle(nullptr)
{
}

DynLoader::~DynLoader() {
  close();
}

void DynLoader::open() {
  _handle = dlopen(_filename.c_str(), RTLD_LAZY);

  if (_handle == nullptr)
    printf("Failed to load library: %s, error %s\n", _filename.c_str(), dlerror());

  dlerror(); // Clear any existing error
}

void DynLoader::close() {
  if (nullptr != _handle) {
    dlclose(_handle);

    printf("Unloaded library: %s\n", _filename.c_str());
  }
}
