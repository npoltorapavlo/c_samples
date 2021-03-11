#ifndef C_SAMPLES_DEVICELOADER_H
#define C_SAMPLES_DEVICELOADER_H

#include "model/device.h"

#include <memory>
#include <list>

class DeviceLoader {
public:
  typedef std::shared_ptr<Device> DevicePtr;
  typedef std::list<DevicePtr> Devices;

  virtual ~DeviceLoader() = default;

  virtual Devices Load() = 0;
};

#endif //C_SAMPLES_DEVICELOADER_H
