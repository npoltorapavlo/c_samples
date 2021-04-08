#ifndef C_SAMPLES_BASE64_H
#define C_SAMPLES_BASE64_H

#include <string>

namespace Base64 {
  std::string encode(const std::string &in);
  std::string decode(const std::string &in);
} // namespace Base64

#endif //C_SAMPLES_BASE64_H
