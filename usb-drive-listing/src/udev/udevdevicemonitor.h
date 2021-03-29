#ifndef C_SAMPLES_UDEVDEVICEMONITOR_H
#define C_SAMPLES_UDEVDEVICEMONITOR_H

#include "devicemonitor.h"

#include <condition_variable>
#include <thread>
#include <mutex>

class UdevDeviceMonitor : public DeviceMonitor {
public:
  UdevDeviceMonitor() = delete;
  UdevDeviceMonitor(const ActionFunction& callback);
  virtual ~UdevDeviceMonitor();

  virtual void Start();
  virtual void Stop();

private:
  static void threadRun(UdevDeviceMonitor *m);

  std::thread m_monitor;
  std::mutex m_monitoringMutex;
  std::condition_variable m_cond;
  bool m_stopMonitoring;
};

#endif //C_SAMPLES_UDEVDEVICEMONITOR_H
