#include "systemclient.h"

#include <list>

using namespace std;

const string systemCallsign = "org.rdk.System.1";

const list<string> systemMethods = {
    "requestSystemUptime",
    "getDeviceInfo",
    "getMode",
    //"getFirmwareUpdateInfo", // sometimes timeouts
    "getNetworkStandbyMode",
    "getPreferredStandbyMode",
    "getAvailableStandbyModes",
    "getXconfParams",
    //"getSerialNumber", // sometimes crashes
    "getFirmwareDownloadPercent",
    "getDownloadedFirmwareInfo",
    "getFirmwareUpdateState",
    //"getMacAddresses", // sometimes timeouts
    "getTimeZoneDST",
    "getCoreTemperature",
    "getPreviousRebootInfo",
    "getLastDeepSleepReason",
    "getPreviousRebootReason",
    //"getMilestones", // sometimes an overflow is seen
    "isGzEnabled",
    "getSystemVersions",
    "getPowerStateIsManagedByDevice",
    "getPowerStateBeforeReboot",
};

const list<string> systemEvents = {
    "onSystemPowerStateChanged",
    "onSystemModeChanged",
    "onFirmwareUpdateInfoReceived",
    "onFirmwareUpdateStateChange",
    "onTemperatureThresholdChanged",
    "onMacAddressesRetreived",
    "onRebootRequest",
    "onSystemClockSet",
};

SystemClient::SystemClient() : client(new ThunderAccess(systemCallsign)) {}

bool SystemClient::PrintInfo() {
  bool result = true;

  uint32_t status = client->ActivatePlugin();
  printf("ActivatePlugin, callsign=%s, status=%d\n", systemCallsign.c_str(), status);
  if (status != 0) {
    result = false;
  }

  list<string> subscribedEvents;

  for (auto const &i : systemEvents) {
    uint32_t status = client->SubscribeEvent(i, std::bind(&SystemClient::thunderEventHandler, this,
                                                          std::placeholders::_1));
    printf("SubscribeEvent, callsign=%s, event=%s, status=%d\n", systemCallsign.c_str(), i.c_str(), status);
    if (status != 0) {
      result = false;
    } else {
      subscribedEvents.emplace_front(i);
    }
  }

  for (auto const &i : systemMethods) {
    JsonObject params, resultObject;
    status = client->InvokeJSONRPC(i, params, resultObject);
    if (0 == status) {
      string resultString;
      resultObject.ToString(resultString);
      printf("InvokeJSONRPC, callsign=%s, method=%s, status=0, result=%s\n", systemCallsign.c_str(), i.c_str(),
             resultString.c_str());
    } else {
      printf("InvokeJSONRPC, callsign=%s, method=%s, status=%d\n", systemCallsign.c_str(), i.c_str(), status);
      result = false;
    }
  }

  // NOTE
  // Unsubscribe only subscribed events. Otherwise ASSERT is hit.
  for (auto const &i : subscribedEvents) {
    client->UnSubscribeEvent(i);
  }

  return result;
}

void SystemClient::thunderEventHandler(const JsonObject& params) {
  string eventParams;
  params.ToString(eventParams);

  printf("thunderEventHandler, callsign=%s, eventParams=%s\n", systemCallsign.c_str(), eventParams.c_str());
}
