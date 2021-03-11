#include "sysdeviceloader.h"

#include <dirent.h>
#include <algorithm>

using namespace std;

namespace {
  DeviceLoader::DevicePtr create(const string& node, const std::string &sysname, Device::Devtype devtype) {
    return std::make_shared<Device>(node, sysname, devtype);
  }

  void enumerate(DeviceLoader::Devices& result) {
    list <string> devices;

    DIR *dir = opendir("/sys/block/");
    if (dir != nullptr) {
      struct dirent *d;
      while ((d = readdir(dir)) != nullptr) {
        if (string(d->d_name).rfind("sd", 0) == 0)
          devices.emplace_back(d->d_name);
      }
      closedir(dir);
    }

    devices.erase(remove_if(devices.begin(), devices.end(), [](const string &device) {
      bool removable = false;

      string path = "/sys/block/" + device + "/removable";
      FILE *file = fopen(path.c_str(), "r");
      if (file != nullptr) {
        char flag;
        if ((fread(&flag, 1, 1, file) == 1) && (flag == '1'))
          removable = true;
        fclose(file);
      }

      return !removable;
    }), devices.end());

    for_each(devices.begin(), devices.end(), [&](const string &device) {
      result.emplace_back(create("/dev/" + device, device, Device::Devtype::disk));

      string path = "/sys/block/" + device;
      DIR *dir = opendir(path.c_str());
      if (dir != nullptr) {
        struct dirent *d;
        while ((d = readdir(dir)) != nullptr) {
          string partition = d->d_name;
          if (d->d_type == DT_DIR && partition.rfind(device, 0) == 0) {
            result.emplace_back(create("/dev/" + partition, partition, Device::Devtype::partition));
          }
        }
        closedir(dir);
      }
    });
  }
}

DeviceLoader::Devices SysDeviceLoader::Load() {
  Devices devices;

  enumerate(devices);

  return devices;
}
