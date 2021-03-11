#ifndef C_SAMPLES_DEVICEMONITOR_H
#define C_SAMPLES_DEVICEMONITOR_H

#include "model/device.h"

#include <memory>
#include <functional>

class DeviceMonitor {
public:
  typedef enum {
    add = 0,
    remove,
  } Action;

  typedef std::shared_ptr<Device> DevicePtr;
  typedef std::function<void(const DevicePtr& device, Action action)> ActionFunction;

  DeviceMonitor() = delete;
  DeviceMonitor(const ActionFunction& callback) : m_Callback(callback) {}
  virtual ~DeviceMonitor() = default;

  virtual void Start() = 0;
  virtual void Stop() = 0;

protected:
  virtual void Notify(const DevicePtr& device, Action action) const {
    if (m_Callback != nullptr) {
      m_Callback(device, action);
    }
  }

protected:
  ActionFunction m_Callback;
};

#endif //C_SAMPLES_DEVICEMONITOR_H
