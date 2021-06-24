#ifndef C_SAMPLES_IARMUTILS_H
#define C_SAMPLES_IARMUTILS_H

namespace Utils {
  struct IARM {
    static bool init();
    static bool isConnected();

    static const char* NAME;
  };
}

#endif //C_SAMPLES_IARMUTILS_H
