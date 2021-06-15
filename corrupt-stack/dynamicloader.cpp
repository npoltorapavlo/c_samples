#include "dynamicloader.h"

#include <dlfcn.h>

DynamicLoader::DynamicLoader(const char* filename)
 : m_filename(filename)
 , m_dynamicHandle(nullptr)
{
}

DynamicLoader::~DynamicLoader() {
  close();
}

void DynamicLoader::open() {
  m_dynamicHandle = dlopen(m_filename.c_str(), RTLD_LAZY);

  if (m_dynamicHandle == nullptr)
    printf("Failed to load library: %s, error %s\n", m_filename.c_str(), dlerror());

  dlerror(); // Clear any existing error
}

void DynamicLoader::close() {
  if (nullptr != m_dynamicHandle) {
    dlclose(m_dynamicHandle);

    printf("Unloaded library: %s\n", m_filename.c_str());
  }
}

void* DynamicLoader::lookup(const char* symbolStr) {
  return dlsym(m_dynamicHandle, symbolStr);
}
