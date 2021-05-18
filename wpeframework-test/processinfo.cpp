#include "processinfo.h"

using namespace std;

const string controllerCallsign = "Controller.1";
const string controllerMethodProcessinfo = "processinfo";

ProcessInfo::ProcessInfo() : client(new ThunderAccess(controllerCallsign)) {}

bool ProcessInfo::PrintInfo() {
  bool result = false;

  JsonObject resultObject;
  uint32_t status = client->Get(controllerMethodProcessinfo, resultObject);
  if (0 == status) {
    string resultString;
    resultObject.ToString(resultString);
    printf("Get, callsign=%s, method=%s, status=0, result=%s\n", controllerCallsign.c_str(),
           controllerMethodProcessinfo.c_str(),
           resultString.c_str());
  } else {
    printf("Get, callsign=%s, method=%s, status=%d\n", controllerCallsign.c_str(), controllerMethodProcessinfo.c_str(),
           status);
    result = false;
  }

  return result;
}
