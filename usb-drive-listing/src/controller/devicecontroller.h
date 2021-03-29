#ifndef C_SAMPLES_DEVICECONTROLLER_H
#define C_SAMPLES_DEVICECONTROLLER_H

#include "model/device.h"
#include "model/mount.h"

#include <map>
#include <list>
#include <memory>
#include <functional>

class DeviceController {
public:
  typedef std::shared_ptr<Device> DevicePtr;
  typedef std::shared_ptr<Mount> MountPtr;
  typedef std::list<DevicePtr> Devices;
  typedef std::map<DevicePtr, MountPtr> DeviceMountMap;
  typedef std::function<void()> UpdateFunction;

  DeviceController() = delete;
  DeviceController(const UpdateFunction& callback) : m_callback(callback) {}
  virtual ~DeviceController() = default;

  virtual void Load() = 0;
  virtual void Monitor() = 0;
  virtual void DeMonitor() = 0;

  Devices GetDevices() { return m_devices; }
  DeviceMountMap DeviceMounts() { return m_deviceMounts; }

protected:
  virtual void Notify() const {
    if (m_callback != nullptr) {
      m_callback();
    }
  }

protected:
  UpdateFunction m_callback;
  Devices m_devices;
  DeviceMountMap m_deviceMounts;
};

#endif //C_SAMPLES_DEVICECONTROLLER_H
