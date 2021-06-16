#include "textgen.h"

#include <algorithm>
#include <cstring>

using namespace std;

namespace TextGen {
  
string generateRandomString(size_t length, const char* charmap) {
  const size_t charmapLength = strlen(charmap);
  auto generator = [&]() { return charmap[rand() % charmapLength]; };
  string result;
  result.reserve(length);
  generate_n(back_inserter(result), length, generator);
  return result;
}

} // namespace TextGen
