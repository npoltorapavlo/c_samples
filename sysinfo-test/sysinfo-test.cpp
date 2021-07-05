#include "sysutils.h"

#include <cstdio>

#define LOW_MEMORY_THRESHOLD_MB 100

using namespace std;

int main(int argc, char** argv) {

  Data data;
  bool isBelowThreshold;
  if (SysUtils::checkRam(LOW_MEMORY_THRESHOLD_MB, data, isBelowThreshold)) {
    int32_t freeKb = -1;
    freeKb = data.toInteger32();
    printf("%s:%d [%s] freeKb: %d isBelowThreshold: %s\n",
           __FILE__, __LINE__, __func__, freeKb, (isBelowThreshold ? "yes" : "no"));
  } else {
    printf("%s:%d [%s] failed to check ram\n",
           __FILE__, __LINE__, __func__);
  }

  return 0;
}
