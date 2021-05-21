#include <core/core.h>
#include <websocket/websocket.h>
#include <securityagent/SecurityTokenUtil.h>

using namespace std;
using namespace WPEFramework;

#define SERVER_DETAILS  "127.0.0.1:9998"
#define MAX_LENGTH 1024

namespace {
  int sToken(string &token) {
    unsigned char buffer[MAX_LENGTH] = {0};
    int tokenStatus = GetSecurityToken(MAX_LENGTH, buffer);

    if (tokenStatus > 0) {
      token = (char *) buffer;
    }

    printf("sToken, tokenStatus=%d, token=%s\n", tokenStatus, token.c_str());

    return tokenStatus;
  }

  string GetJsonObjectResultString(const JsonObject& jsonObject) {
    string result;
    jsonObject.ToString(result);
    return result;
  }
} // namespace

int main(int argc, char** argv) {
  
  bool useToken = ((argc > 1) && (string(argv[1]) == "true"));
  bool activateSystem = ((argc > 2) && (string(argv[2]) == "true"));

  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T(SERVER_DETAILS)));

  string token, query;
  if (useToken)
  {
    if (sToken(token) > 0) {
      query = "token=" + token;
    }
  }

  auto controllerObject = new JSONRPC::LinkType<Core::JSON::IElement>(_T(""), nullptr, false, query);
  auto systemInstance = new JSONRPC::LinkType<Core::JSON::IElement>(_T("org.rdk.System.1"), nullptr, false, query);

  if (activateSystem)
  {
    JsonObject params;
    JsonObject result;
    params["callsign"] = "org.rdk.System.1";
    auto errCode = controllerObject->Invoke<JsonObject, JsonObject>(1000, _T("activate"), params, result);
    if ( errCode == WPEFramework::Core::ERROR_NONE )
    {
      printf( "System activation succeeded\n" );
    }
    else
    {
      printf( "System activation failed, errCode: %u\n", errCode );
    }
  }

  {
    // https://ccp.sys.comcast.net/browse/XIONE-4258
    JsonObject params;
    JsonObject result;
    auto errCode = systemInstance->Invoke<JsonObject, JsonObject>(1000, _T("getPowerStateBeforeReboot"), params, result );
    if ( (errCode == WPEFramework::Core::ERROR_NONE) && (result["success"].Boolean()) )
    {
      printf( "getPowerStateBeforeReboot succeeded\n" );
    }
    else
    {
      printf( "getPowerStateBeforeReboot failed, errCode: %u, result: '%s'\n", errCode, GetJsonObjectResultString(result).c_str() );
    }
  }

  delete systemInstance;
  delete controllerObject;

  return 0;
}
