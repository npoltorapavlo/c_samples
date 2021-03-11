#ifndef C_SAMPLES_SYSDEVICELOADER_H
#define C_SAMPLES_SYSDEVICELOADER_H

#include "deviceloader.h"

class SysDeviceLoader : public DeviceLoader {
public:
  virtual Devices Load();
};

#endif //C_SAMPLES_SYSDEVICELOADER_H
