#include "rfcutils.h"

#include "rfcapi.h"

using namespace std;

namespace RFCUtils {

bool getRFC(const string &name, string &value, const string &caller) {
  bool result = false;
  RFC_ParamData_t param = {0};
  printf("%s name = %s, caller = %s\n", __FUNCTION__, name.c_str(), caller.c_str());
  WDMP_STATUS status = getRFCParameter(const_cast<char *>(caller.c_str()), name.c_str(), &param);
  if (status == WDMP_SUCCESS) {
    printf("%s name = %s, type = %d, value = %s\n", __FUNCTION__, param.name, param.type, param.value);
    value = param.value;
    result = true;
  } else {
    printf("getRFC Failed: %d %s\n", status, getRFCErrorString(status));
  }
  return result;
}

bool setRFC(const string &name, const string &value, const string &caller) {
  bool result = false;
  printf("%s name = %s, type = %d, value = %s, caller = %s\n", __FUNCTION__, name.c_str(), WDMP_STRING, value.c_str(), caller.c_str());
  WDMP_STATUS status = setRFCParameter(const_cast<char *>(caller.c_str()), name.c_str(), value.c_str(), WDMP_STRING);
  if (status == WDMP_SUCCESS) {
    result = true;
  } else {
    printf("setRFC Failed: %d %s\n", status, getRFCErrorString(status));
  }
  return result;
}

} // namespace RFCUtils
