#include "whclient.h"

using namespace std;

const string whCallsign = "org.rdk.Warehouse.1";

const string whMethod = "isClean";

WhClient::WhClient() : client(new ThunderAccess(whCallsign)) {}

bool WhClient::PrintInfo() {
  bool result = true;

  uint32_t status = client->ActivatePlugin();
  printf("ActivatePlugin, callsign=%s, status=%d\n", whCallsign.c_str(), status);
  if (status != 0) {
    result = false;
  }

  JsonObject params, resultObject;
  status = client->InvokeJSONRPC(whMethod, params, resultObject);
  if (0 == status) {
    string resultString;
    resultObject.ToString(resultString);
    printf("InvokeJSONRPC, callsign=%s, method=%s, status=0, result=%s\n", whCallsign.c_str(), whMethod.c_str(),
           resultString.c_str());
  } else {
    printf("InvokeJSONRPC, callsign=%s, method=%s, status=%d\n", whCallsign.c_str(), whMethod.c_str(), status);
    result = false;
  }

  return result;
}
