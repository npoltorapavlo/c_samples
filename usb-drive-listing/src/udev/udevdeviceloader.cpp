#include "udevdeviceloader.h"

#include <libudev.h>
#include <regex>

using namespace std;

namespace {
  DeviceLoader::DevicePtr create(struct udev_device *dev, Device::Devtype devtype) {
    return std::make_shared<Device>(udev_device_get_devnode(dev), udev_device_get_sysname(dev), devtype);
  }

  void enumerate(DeviceLoader::Devices& result) {
    struct udev *udev = udev_new();

    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "block");
    udev_enumerate_scan_devices(enumerate);

    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;

    if (devices) {
      udev_list_entry_foreach(entry, devices) {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);

        struct udev_device *usb
            = udev_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_device");
        if (usb) {
          string devtype = udev_device_get_devtype(dev);
          if (regex_match(devtype, regex("(partition|disk)"))) {
            result.emplace_back(create(dev, devtype == "partition" ? Device::Devtype::partition : Device::Devtype::disk));
          }
        }

        udev_device_unref(dev);
      }
    }

    udev_enumerate_unref(enumerate);

    udev_unref(udev);
  }
}

DeviceLoader::Devices UdevDeviceLoader::Load() {
  Devices devices;

  enumerate(devices);

  return devices;
}
