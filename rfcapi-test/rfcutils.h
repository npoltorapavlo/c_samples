#ifndef C_SAMPLES_RFCUTILS_H
#define C_SAMPLES_RFCUTILS_H

#include <string>

namespace RFCUtils {
  bool getRFC(const std::string &name, std::string &value, const std::string &caller = std::string("test"));

  bool setRFC(const std::string &name, const std::string &value, const std::string &caller = std::string("test"));
}

#endif //C_SAMPLES_RFCUTILS_H
