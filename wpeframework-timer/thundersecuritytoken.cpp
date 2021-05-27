#include "thundersecuritytoken.h"

#include <securityagent/SecurityTokenUtil.h>

#include <mutex>

#define MAX_STRING_LENGTH 2048

using namespace std;

namespace ThunderSecurityToken {

bool getSecurityToken(std::string& token) {
  bool result = false;

  static std::mutex mtx;
  std::unique_lock <std::mutex> lock(mtx);

  static bool thunderSecurityChecked = false;
  static string sToken = "";

  if (thunderSecurityChecked) {
    token = sToken;
    result = true;
  } else {
    thunderSecurityChecked = true;

    unsigned char buffer[MAX_STRING_LENGTH] = {0};
    int ret = GetSecurityToken(MAX_STRING_LENGTH, buffer);
    printf("token status: %d\n", ret);

    if (ret >= 0) {
      token = (char *) buffer;
      sToken = token;
      result = true;
    }
  }

  return result;
}

} //namespace ThunderSecurityToken
