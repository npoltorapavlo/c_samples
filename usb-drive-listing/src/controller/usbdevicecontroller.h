#ifndef C_SAMPLES_USBDEVICECONTROLLER_H
#define C_SAMPLES_USBDEVICECONTROLLER_H

#include "devicecontroller.h"
#include "devicemonitor.h"
#include "mountloader.h"

#include <typeinfo>
#include <algorithm>

class UsbDeviceController : public DeviceController {
public:
  typedef std::shared_ptr <DeviceMonitor> DeviceMonitorPtr;
  typedef std::list <DeviceMonitorPtr> DeviceMonitors;

  UsbDeviceController() = delete;
  UsbDeviceController(const UpdateFunction& callback) : DeviceController(callback) {}
  virtual ~UsbDeviceController() = default;

  virtual void Load();
  virtual void Monitor();
  virtual void DeMonitor();

  template<typename DEVICELOADER, typename MOUNTLOADER>
  void Load() {
    std::shared_ptr <DEVICELOADER> deviceLoader(new DEVICELOADER);
    Devices devices = deviceLoader->Load();
    for (auto const &i : devices) {
      AddDevice(i);
      AddMount<MOUNTLOADER>(i);
    }
  }

  template<typename MONITOR, typename MOUNTLOADER>
  void Monitor() {
    DeMonitor < MONITOR > ();
    DeviceMonitorPtr monitor(new MONITOR(std::bind(&UsbDeviceController::MonitorAction<MOUNTLOADER>, this,
                                                   std::placeholders::_1, std::placeholders::_2)));
    monitor->Start();
    m_monitors.emplace_back(monitor);
  }

  template<typename MONITOR>
  void DeMonitor() {
    m_monitors.erase(std::remove_if(m_monitors.begin(), m_monitors.end(),
                                    [](const DeviceMonitorPtr &monitor) {
                                      return std::is_same<MONITOR, std::remove_pointer<decltype(monitor.get())>::type>::value;
                                    }),
                     m_monitors.end());
  }

private:
  template<typename MOUNTLOADER>
  void MonitorAction(const DevicePtr &device, DeviceMonitor::Action action)  {
    if (action == DeviceMonitor::Action::add) {
      AddDevice(device);
      // TODO: device is not yet mounted here, need a delay
      AddMount<MOUNTLOADER>(device);
      Notify();
    } else if (action == DeviceMonitor::Action::remove) {
      RemoveDevice(device);
      RemoveMount(device);
      Notify();
    }
  }

  template<typename MOUNTLOADER>
  void AddMount(const DevicePtr& device) {
    std::shared_ptr <MOUNTLOADER> mountLoader(new MOUNTLOADER);
    MountPtr mount = mountLoader->Load(device->Node());
    auto it = std::find_if(m_deviceMounts.begin(), m_deviceMounts.end(),
                           [&device](const std::pair<DevicePtr, MountPtr> & t) -> bool {
                             return t.first->Node() == device->Node();
                           }
    );
    if (it != m_deviceMounts.end())
      it->second = mount;
    else
      m_deviceMounts.emplace(device, mount);
  }

  void AddDevice(const DevicePtr& device);
  void RemoveDevice(const DevicePtr& device);
  void RemoveMount(const DevicePtr& device);

  DeviceMonitors m_monitors;
};

#endif //C_SAMPLES_USBDEVICECONTROLLER_H
