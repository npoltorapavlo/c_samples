#pragma once

#include <string>

class DynamicLoader {
public:
  DynamicLoader(const char* filename);
  virtual ~DynamicLoader();

  void open();
  void close();

  void* lookup(const char* symbolStr);

private:
  const std::string m_filename;
  void* m_dynamicHandle;
};
