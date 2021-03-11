#include "usbdevicecontroller.h"

#include "udev/udevdeviceloader.h"
#include "udev/udevdevicemonitor.h"

#include "sys/sysdeviceloader.h"
#include "sys/mntentloader.h"

void UsbDeviceController::Load() {
  Load<UdevDeviceLoader, MntentLoader>();
  Load<SysDeviceLoader, MntentLoader>();
}

void UsbDeviceController::Monitor() {
  Monitor<UdevDeviceMonitor, MntentLoader>();
}

void UsbDeviceController::DeMonitor() {
  DeMonitor<UdevDeviceMonitor>();
}

void UsbDeviceController::AddDevice(const DevicePtr& device) {
  Device* d = device.get();

  bool found = false;
  Devices::iterator it;
  for (it = m_devices.begin(); it != m_devices.end(); it++) {
    Device* i = it->get();
    if (*i == *d) {
      found = true;
      break;
    } else if (i->Node() == d->Node()) {
      found = true;
      *i = *d;
      break;
    }
  }

  if (!found) {
    m_devices.emplace_back(device);
  }
}

void UsbDeviceController::RemoveDevice(const DevicePtr& device) {
  m_devices.erase(std::remove_if(m_devices.begin(), m_devices.end(),
                                 [&device](const DevicePtr& i) {
                                   return i->Node() == device->Node();
                                 }),
                  m_devices.end());
}

void UsbDeviceController::RemoveMount(const DevicePtr& device) {
  auto it = std::find_if(m_deviceMounts.begin(), m_deviceMounts.end(),
                         [&device](const std::pair<DevicePtr, MountPtr> & t) -> bool {
                           return t.first->Node() == device->Node();
                         }
  );
  if (it != m_deviceMounts.end())
    m_deviceMounts.erase(it);
}
