#ifndef C_SAMPLES_UDEVDEVICELOADER_H
#define C_SAMPLES_UDEVDEVICELOADER_H

#include "deviceloader.h"

class UdevDeviceLoader : public DeviceLoader {
public:
  virtual Devices Load();
};

#endif //C_SAMPLES_UDEVDEVICELOADER_H
