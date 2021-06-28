#include "sysutils.h"

#include <sys/sysinfo.h>

#include <cstdio>
#include <cerrno>
#include <string.h>

namespace SysUtils {
  bool ram(uint32_t &freeKb, uint32_t &totalKb, uint32_t &usedSwapKb) {
    bool result = false;

    struct sysinfo si;
    int ret = sysinfo(&si);
    if (ret != 0) {
      printf("%s:%d [%s] sysinfo %d (%s)\n",
             __FILE__, __LINE__, __func__, errno, strerror(errno));
    } else {
      totalKb = si.totalram / (1024);
      freeKb = si.freeram / (1024);
      usedSwapKb = (si.totalswap - si.freeswap) / 1024;
      result = true;

      printf("%s:%d [%s] sysinfo: %u %u %u (mem_unit=%u)\n",
             __FILE__, __LINE__, __func__, freeKb, totalKb, usedSwapKb, si.mem_unit);
    }

    return result;
  }

  bool checkRam(double thresholdMb, Data &data, bool &isBelowThreshold) {
    bool result = false;

    uint32_t freeKb = 0, usedKb = 0, totalKb = 0;
    if (ram(freeKb, totalKb, usedKb)) {
      float freeMb = freeKb / 1024;
      data = freeKb;
      result = true;
      if (freeMb < thresholdMb) {
        printf("%s:%d [%s] ram %f below %f\n",
               __FILE__, __LINE__, __func__, freeMb, thresholdMb);
        isBelowThreshold = true;
      } else {
        isBelowThreshold = false;
      }
    }

    return result;
  }
}
