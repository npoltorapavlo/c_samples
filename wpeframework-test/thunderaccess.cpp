#include "thunderaccess.h"

#include <securityagent/SecurityTokenUtil.h>

#include <mutex>

using namespace std;
using namespace WPEFramework;

#define SERVER_DETAILS  "127.0.0.1:9998"
#define MAX_LENGTH 1024
#define THUNDER_RPC_TIMEOUT 5000

namespace {
  std::mutex sTokenMutex;

  int sToken(string &token) {
    unsigned char buffer[MAX_LENGTH] = {0};

    // NOTE
    // Multiple threads calling GetSecurityToken cause "ipclink.cpp:85 [GetToken] Could not open link. error=-1",
    // resulting in "status 3" on JSONRPC::LinkType with no token.
    std::unique_lock <std::mutex> lock(sTokenMutex);
    int tokenStatus = GetSecurityToken(MAX_LENGTH, buffer);
    lock.unlock();

    if (tokenStatus > 0) {
      token = (char *) buffer;
    }

    printf("sToken, tokenStatus=%d, token=%s\n", tokenStatus, token.c_str());

    return tokenStatus;
  }
} // namespace

ThunderAccess::ThunderAccess(const std::string &callsign)
  : remoteObject(NULL)
  , controllerObject(NULL)
  , pluginCallsign(callsign) {
  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T(SERVER_DETAILS)));

  string token, query;
  if (sToken(token) > 0) {
    query = "token=" + token;
  }

  // NOTE
  // If second arg is nullptr, id is generated (ex. "temporary6").
  // If second arg is "", id is "". Multiple clients with the same id ("") can conflict causing
  // an ASSERT like this: "Do not unregister methods that are not registered!!!"
  controllerObject = new JSONRPC::LinkType<Core::JSON::IElement>(_T(""), nullptr, false, query);
  remoteObject = new JSONRPC::LinkType<Core::JSON::IElement>(_T(pluginCallsign), nullptr, false, query);
}

ThunderAccess::~ThunderAccess() {
  delete controllerObject;
  delete remoteObject;
}

uint32_t ThunderAccess::ActivatePlugin() {
  JsonObject controlParam, result;
  controlParam["callsign"] = pluginCallsign;
  return controllerObject->Invoke<JsonObject, JsonObject>(THUNDER_RPC_TIMEOUT, _T("activate"), controlParam, result);
}

uint32_t ThunderAccess::SubscribeEvent(const std::string &eventName, std::function<void(const WPEFramework::Core::JSON::VariantContainer&)> functionHandler) {
  return remoteObject->Subscribe<JsonObject>(THUNDER_RPC_TIMEOUT, _T(eventName), functionHandler);
}

void ThunderAccess::UnSubscribeEvent(const std::string &eventName) {
  remoteObject->Unsubscribe(THUNDER_RPC_TIMEOUT, _T(eventName));
}

uint32_t ThunderAccess::InvokeJSONRPC(const std::string &method, const JsonObject &param, JsonObject &result) {
  return remoteObject->Invoke<JsonObject, JsonObject>(THUNDER_RPC_TIMEOUT, _T(method), param, result);
}

uint32_t ThunderAccess::Get(const std::string &method, JsonObject &result) {
  return remoteObject->Get<JsonObject>(THUNDER_RPC_TIMEOUT, _T(method), result);
}
