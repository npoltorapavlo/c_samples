#ifndef C_SAMPLES_MOUNTLOADER_H
#define C_SAMPLES_MOUNTLOADER_H

#include "model/mount.h"

#include <memory>

class MountLoader {
public:
  typedef std::shared_ptr<Mount> MountPtr;

  virtual ~MountLoader() = default;

  virtual MountPtr Load(const std::string& node) = 0;
};

#endif //C_SAMPLES_MOUNTLOADER_H
