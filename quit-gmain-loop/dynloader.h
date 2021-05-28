#pragma once

#include <string>

class DynLoader {
public:
  DynLoader(const char* filename);
  virtual ~DynLoader();

  void open();
  void close();

private:
  const std::string _filename;
  void* _handle;
};
