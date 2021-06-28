#ifndef C_SAMPLES_SYSUTILS_H
#define C_SAMPLES_SYSUTILS_H

#include "data.h"

namespace SysUtils {
  bool ram(uint32_t &freeKb, uint32_t &totalKb, uint32_t &usedSwapKb);
  bool checkRam(double thresholdMb, Data &data, bool &isBelowThreshold);
};

#endif //C_SAMPLES_SYSUTILS_H
