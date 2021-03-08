#pragma once

#include <memory>

class ISharedLibraryImp {
public:
  virtual ~ISharedLibraryImp() {}

  virtual void startThread() noexcept = 0;
};

extern "C" {
void create(std::shared_ptr<ISharedLibraryImp>& ptr);
}
