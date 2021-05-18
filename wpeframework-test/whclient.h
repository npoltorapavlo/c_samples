#ifndef C_SAMPLES_WHCLIENT_H
#define C_SAMPLES_WHCLIENT_H

#include "thunderaccess.h"

#include <memory>

class WhClient {
public:
  WhClient();
  ~WhClient() = default;

  bool PrintInfo();

private:
  std::unique_ptr <ThunderAccess> client;
};

#endif //C_SAMPLES_WHCLIENT_H
