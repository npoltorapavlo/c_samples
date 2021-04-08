#include "base64.h"

#include <vector>

namespace Base64 {

const char* symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::vector<int> initT() {
  std::vector<int> T(256,-1);
  for (int i=0; i<64; i++) T[symbols[i]] = i;
  return T;
}

std::vector<int> T = initT();

// from https://stackoverflow.com/a/34571089
std::string encode(const std::string &in) {
  std::string out;

  int val = 0, valb = -6;
  for (unsigned char c : in) {
    val = (val << 8) + c;
    valb += 8;
    while (valb >= 0) {
      out.push_back(symbols[(val>>valb)&0x3F]);
      valb -= 6;
    }
  }
  if (valb>-6) out.push_back(symbols[((val<<8)>>(valb+8))&0x3F]);
  while (out.size()%4) out.push_back('=');
  return out;
}

std::string decode(const std::string &in) {
  std::string out;

  int val=0, valb=-8;
  for (unsigned char c : in) {
    if (T[c] == -1) break;
    val = (val << 6) + T[c];
    valb += 6;
    if (valb >= 0) {
      out.push_back(char((val>>valb)&0xFF));
      valb -= 8;
    }
  }
  return out;
}

} // namespace Base64
