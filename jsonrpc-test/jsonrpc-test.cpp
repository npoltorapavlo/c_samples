#ifndef MODULE_NAME
#define MODULE_NAME Sample_WPEFrameworkErrcode
#endif

#include <core/core.h>
#include <websocket/websocket.h>
#include <securityagent/SecurityTokenUtil.h>

MODULE_NAME_DECLARATION(BUILD_REFERENCE)

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
  bool activate = ((argc > 2) && (string(argv[2]) == "true"));
  const char* plugin = ((argc > 3) ? argv[3] : "org.rdk.System.1");
  const char* method = ((argc > 4) ? argv[4] : "getPowerStateBeforeReboot");

  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T(SERVER_DETAILS)));

  string token, query;
  if (useToken)
  {
    if (sToken(token) > 0) {
      query = "token=" + token;
    }
  }

  auto controllerObject = new JSONRPC::LinkType<Core::JSON::IElement>(_T(""), nullptr, false, query);
  auto pluginInstance = new JSONRPC::LinkType<Core::JSON::IElement>(_T(plugin), nullptr, false, query);

  if (activate)
  {
    JsonObject params;
    JsonObject result;
    params["callsign"] = plugin;
    auto errCode = controllerObject->Invoke<JsonObject, JsonObject>(1000, _T("activate"), params, result);
    if ( errCode == WPEFramework::Core::ERROR_NONE )
    {
      printf( "activate succeeded\n" );
    }
    else
    {
      printf( "activate failed, errCode: %u (%d)\n", errCode, errCode );
    }
  }

  if (*method)
  {
    // https://ccp.sys.comcast.net/browse/XIONE-4258
    JsonObject params;
    JsonObject result;
    auto errCode = pluginInstance->Invoke<JsonObject, JsonObject>(1000, _T(method), params, result );
    if ( (errCode == WPEFramework::Core::ERROR_NONE) && (result["success"].Boolean()) )
    {
      printf( "method succeeded\n" );
    }
    else
    {
      printf( "method failed, errCode: %u (%d), result: '%s'\n", errCode, errCode, GetJsonObjectResultString(result).c_str() );
    }
  }

  delete pluginInstance;
  delete controllerObject;

  return 0;
}
