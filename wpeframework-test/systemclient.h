#ifndef C_SAMPLES_SYSTEMCLIENT_H
#define C_SAMPLES_SYSTEMCLIENT_H

#include "thunderaccess.h"

#include <memory>

class SystemClient {
public:
  SystemClient();
  ~SystemClient() = default;

  bool PrintInfo();

private:
  void thunderEventHandler(const JsonObject &params);

  std::unique_ptr <ThunderAccess> client;
};

#endif //C_SAMPLES_SYSTEMCLIENT_H
