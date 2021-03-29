#ifndef C_SAMPLES_STDOUTPUT_H
#define C_SAMPLES_STDOUTPUT_H

#include "output.h"

#include <time.h>

template<typename DEVICECONTROLLER>
class StdOutput : public Output<DEVICECONTROLLER> {
public:
  typedef std::shared_ptr<Device> DevicePtr;
  typedef std::shared_ptr<Mount> MountPtr;
  typedef std::map<DevicePtr, MountPtr> DeviceMountMap;

  virtual void Update() {
    DeviceMountMap map = this->m_controller.DeviceMounts();

    DeviceMountMap::const_iterator it = map.begin();

    uint32_t i = 0;

    time_t t = time(nullptr);

    fprintf(stdout, "%s\n", ctime(&t));

    while (it != map.end()) {
      DevicePtr device = it->first;
      Device::Devtype devtype = device->GetDevtype();

      MountPtr mount = it->second;

      std::string node = device->Node();
      std::string sysname = device->Sysname();
      std::string mountStr = mount.get() == nullptr ? "" : ("mounted as " + mount->Path());

      fprintf(stdout, " (%d) %s (%s,%s) %s\n",
              i,
              node.c_str(),
              sysname.c_str(),
              devtype == Device::Devtype::disk ? "disk" : (devtype == Device::Devtype::partition ? "partition" : "???"),
              mountStr.c_str()
      );
      fflush(stdout);

      it++;
      i++;
    }

    fprintf(stdout, "\n");
    fflush(stdout);
  }
};

#endif //C_SAMPLES_STDOUTPUT_H
