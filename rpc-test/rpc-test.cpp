#include "server.h"
#include "client.h"

#include <functional>

#define NDEBUG
#include <cassert>

#define MAX_STRING_LENGTH 2048

using namespace std;
using namespace WPEFramework;

int main(int argc, char** argv) {
  Authenticator authenticator;

  unsigned char buffer[MAX_STRING_LENGTH] = {0};
  string str = "The quick brown fox ...";
  size_t str_hash = hash<string>{}(str);
  string str_hash_str = to_string(str_hash);
  memcpy(buffer, str.c_str(), str.length());

  assert(GetToken(MAX_STRING_LENGTH, str.length(), buffer));

  assert(str_hash_str == buffer);

  return 0;
}
