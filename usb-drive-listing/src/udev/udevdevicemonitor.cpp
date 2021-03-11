#include "udevdevicemonitor.h"

#include <libudev.h>
#include <cassert>
#include <regex>

using namespace std;

namespace {
  DeviceMonitor::DevicePtr create(struct udev_device *dev, Device::Devtype devtype) {
    return std::make_shared<Device>(udev_device_get_devnode(dev), udev_device_get_sysname(dev), devtype);
  }
}

UdevDeviceMonitor::UdevDeviceMonitor(const ActionFunction& callback)
  : DeviceMonitor(callback)
  , m_stopMonitoring(false)
{
}

UdevDeviceMonitor::~UdevDeviceMonitor() {
  Stop();
}

void UdevDeviceMonitor::Start() {
  Stop();

  {
    std::lock_guard<std::mutex> lock(m_monitoringMutex);
    m_stopMonitoring = false;
  }

  m_monitor = std::thread(threadRun, this);
}

void UdevDeviceMonitor::Stop() {
  if (m_monitor.joinable()) {
    {
      std::unique_lock<std::mutex> lock(m_monitoringMutex);
      m_stopMonitoring = true;
      m_cond.notify_one();
    }

    m_monitor.join();
  }
}

void UdevDeviceMonitor::threadRun(UdevDeviceMonitor *m) {
  struct udev *udev = udev_new();
  assert(udev != NULL);

  struct udev_monitor *mon = udev_monitor_new_from_netlink(udev, "udev");
  assert(mon != NULL);

  assert(udev_monitor_filter_add_match_subsystem_devtype(mon, "block", NULL) >= 0);
  assert(udev_monitor_filter_add_match_subsystem_devtype(mon, "usb", "usb-device") >= 0);
  udev_monitor_enable_receiving(mon);

  int fd = udev_monitor_get_fd(mon);
  while (1) {
    fd_set fds;
    struct timeval tv;
    int ret;

    FD_ZERO(&fds); //clear fds
    FD_SET(fd, &fds);// Add fd to fds
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    ret = select(fd + 1, &fds, NULL, NULL, &tv);

    /* Check if our file descriptor has received data. */
    if (ret > 0 && FD_ISSET(fd, &fds)) {
      struct udev_device *dev = udev_monitor_receive_device(mon);
      if (dev) {
        if (udev_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_device") != NULL) {
          string devtype = udev_device_get_devtype(dev);
          string action = udev_device_get_action(dev);

          if (regex_match(action, regex("(add|remove)")) &&
              regex_match(devtype, regex("(partition|disk)"))) {
            m->Notify(
                create(dev, (devtype.compare("partition") == 0) ? Device::Devtype::partition : Device::Devtype::disk),
                (action.compare("add") == 0) ? Action::add : Action::remove
            );
          }
        }

        udev_device_unref(dev);
      }
    }

    std::unique_lock <std::mutex> lock(m->m_monitoringMutex);
    if (m->m_cond.wait_for(lock, std::chrono::milliseconds(250), [&m] { return m->m_stopMonitoring; }))
      break;
  }

  udev_monitor_unref(mon);

  udev_unref(udev);
}
