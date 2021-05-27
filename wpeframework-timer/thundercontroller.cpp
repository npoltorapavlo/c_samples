#include "thundercontroller.h"

#include <plugins/plugins.h>
#include <securityagent/SecurityTokenUtil.h>

#include "thundersecuritytoken.h"

#define SERVER_DETAILS  "127.0.0.1:9998"
#define ACTIVATE_TIME_OUT 2000
#define GET_STATUS_TIME_OUT 2000

using namespace std;
using namespace WPEFramework;

void ThunderController::Init() {
  string token;
  ThunderSecurityToken::getSecurityToken(token);
  string query = "token=" + token;

  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T(SERVER_DETAILS)));
  m_thunderClient =
      make_shared < WPEFramework::JSONRPC::LinkType < WPEFramework::Core::JSON::IElement > >
      ("", "", false, query);
}

bool ThunderController::Activate(const char* callSign) {
  bool result = false;

  JsonObject params, response;
  params.Set("callsign", callSign);

  if (!IsActivated(callSign)) {
    printf("Activating %s\n", callSign);
    uint32_t status = m_thunderClient->Invoke<JsonObject, JsonObject>(ACTIVATE_TIME_OUT, "activate", params, response);
    string strParams;
    string strResponse;
    params.ToString(strParams);
    response.ToString(strResponse);
    printf("Activate with params %s, status: %d, response: %s", strParams.c_str(), status, strResponse.c_str());
    if (status == Core::ERROR_NONE) {
      result = true;
    }
  } else {
    result = true;
  }

  return result;
}

bool ThunderController::IsActivated(const char* callSign) {
  bool result = false;

  string method = "status@" + string(callSign);
  Core::JSON::ArrayType <PluginHost::MetaData::Service> response;
  uint32_t status = m_thunderClient->Get < Core::JSON::ArrayType < PluginHost::MetaData::Service > >
                    (GET_STATUS_TIME_OUT, method.c_str(), response);

  if (status == Core::ERROR_NONE) {
    printf("Getting status for callSign %s, result: %s\n", callSign, response[0].JSONState.Data().c_str());
    result = response[0].JSONState == PluginHost::IShell::ACTIVATED;
  } else {
    printf("Getting status for callSign %s, status: %d\n", callSign, status);
  }

  return result;
}
