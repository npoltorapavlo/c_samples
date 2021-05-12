#include "keyholder.h"

#include "base64.h"

#include <string>
#include <cstring>

using namespace std;

KeyHolder::KeyHolder()
: ptr(nullptr) {
}

KeyHolder::~KeyHolder() {
  if (ptr)
    free(ptr);
}

void KeyHolder::write(long secret) {
  string encoded = Base64::encode(to_string(secret));

  if (ptr && strlen(ptr) == encoded.size())
    strcpy(ptr, encoded.c_str());
  else {
    if (ptr)
      free(ptr);
    ptr = strdup(encoded.c_str());
    assert(ptr != nullptr);
  }
}

long KeyHolder::read() const {
  if (!empty()) {
    return (stol(Base64::decode(string(ptr))));
  }
  return 0;
}

bool KeyHolder::empty() const {
  return (ptr == nullptr);
}
