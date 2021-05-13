#ifndef C_SAMPLES_PROCESSINFO_H
#define C_SAMPLES_PROCESSINFO_H

#include "thunderaccess.h"

#include <memory>

class ProcessInfo {
public:
  ProcessInfo();
  ~ProcessInfo() = default;

  bool PrintInfo();

private:
  void thunderEventHandler(const JsonObject &params);

  std::unique_ptr <ThunderAccess> client;
};

#endif //C_SAMPLES_PROCESSINFO_H
