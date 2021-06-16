#ifndef C_SAMPLES_TEXTGEN_H
#define C_SAMPLES_TEXTGEN_H

#include <string>

namespace TextGen {
  std::string generateRandomString(size_t length, const char *charmap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

#endif //C_SAMPLES_TEXTGEN_H
