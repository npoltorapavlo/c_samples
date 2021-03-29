#ifndef C_SAMPLES_MNTENTLOADER_H
#define C_SAMPLES_MNTENTLOADER_H

#include "mountloader.h"

class MntentLoader : public MountLoader {
public:
  virtual MountPtr Load(const std::string& node);
};

#endif //C_SAMPLES_MNTENTLOADER_H
