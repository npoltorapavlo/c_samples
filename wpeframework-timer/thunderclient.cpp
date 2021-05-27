#include "thunderclient.h"

#include "thundercontroller.h"

#define HDMICECSINK_CALLSIGN "org.rdk.HdmiCecSink"
#define HDMICECSINK_CALLSIGN_VER HDMICECSINK_CALLSIGN".1"
#define HDMICECSINK_ARC_INITIATION_EVENT "arcInitiationEvent"
#define HDMICECSINK_ARC_TERMINATION_EVENT "arcTerminationEvent"
#define HDMICECSINK_SHORT_AUDIO_DESCRIPTOR_EVENT "shortAudiodesciptorEvent"
#define SERVER_DETAILS  "127.0.0.1:9998"
#define WARMING_UP_TIME_IN_SECONDS 5
#define RECONNECTION_TIME_IN_MILLISECONDS 5500
#define SUBSCRIBE_TIME_OUT 1000

using namespace std;
using namespace WPEFramework;

ThunderClient::ThunderClient()
: m_subscribed(false)
{
  m_timer.connect(std::bind(&ThunderClient::onTimer, this));
}

ThunderClient::~ThunderClient() {
  printf("%s\n", __FUNCTION__);
  lock_guard<mutex> lck(m_callMutex);
  printf("%s acquired lock\n", __FUNCTION__);
}

void ThunderClient::Init() {
  m_thunderController.Init();

  if (m_timer.isActive()) {
    m_timer.stop();
  }

  m_thunderController.Activate(HDMICECSINK_CALLSIGN);

  printf("Starting the timer\n");
  m_timer.start(RECONNECTION_TIME_IN_MILLISECONDS);
}

void ThunderClient::DeInit() {
}

bool ThunderClient::subscribeForEvent(const char* eventName, const ThunderClientEventHandler& method) {
  bool result = false;

  uint32_t err = Core::ERROR_NONE;
  printf("Attempting to subscribe for event: %s\n", eventName);
  Core::SystemInfo::SetEnvironment(_T("THUNDER_ACCESS"), (_T(SERVER_DETAILS)));
  if (nullptr == m_client) {
    m_client = make_shared < WPEFramework::JSONRPC::LinkType <
               Core::JSON::IElement >> (_T(HDMICECSINK_CALLSIGN_VER), (_T(HDMICECSINK_CALLSIGN_VER)));
    if (nullptr == m_client) {
      printf("JSONRPC: %s: client initialization failed\n", HDMICECSINK_CALLSIGN_VER);
      err = Core::ERROR_UNAVAILABLE;
    }
  }

  if (err == Core::ERROR_NONE) {
    err = m_client->Subscribe<JsonObject>(SUBSCRIBE_TIME_OUT, eventName, method, this);
    if (err == Core::ERROR_NONE) {
      printf("Subscribed for %s\n", eventName);
      result = true;
    } else {
      printf("Failed to subscribe for %s with code %d\n", eventName, err);
    }
  }

  return result;
}

void ThunderClient::onTimer() {
  printf("%s\n", __FUNCTION__);
  m_callMutex.lock();
  printf("%s acquired lock\n", __FUNCTION__);

  bool pluginActivated = m_thunderController.IsActivated(HDMICECSINK_CALLSIGN);
  if (!m_subscribed) {
    if (pluginActivated &&
        subscribeForEvent(HDMICECSINK_ARC_INITIATION_EVENT, &ThunderClient::onArcInitiationEvent) &&
        subscribeForEvent(HDMICECSINK_ARC_TERMINATION_EVENT, &ThunderClient::onArcTerminationEvent) &&
        subscribeForEvent(HDMICECSINK_SHORT_AUDIO_DESCRIPTOR_EVENT, &ThunderClient::onShortAudiodesciptorEvent)) {
      m_subscribed = true;
      if (m_timer.isActive()) {
        m_timer.stop();
        printf("Timer stopped.\n");
      }
      printf("Subscription completed.\n");
      sleep(WARMING_UP_TIME_IN_SECONDS);
    } else {
      printf("Could not subscribe this time, one more attempt in %d msec. Plugin is %s\n",
             RECONNECTION_TIME_IN_MILLISECONDS, pluginActivated ? "ACTIVE" : "BLOCKED");
      if (!pluginActivated) {
        m_thunderController.Activate(HDMICECSINK_CALLSIGN);
      }
    }
  } else {
    printf("Already subscribed. Stopping the timer.\n");
    if (m_timer.isActive()) {
      m_timer.stop();
    }
  }

  m_callMutex.unlock();
  printf("%s unlocked\n", __FUNCTION__);
}

void ThunderClient::onArcInitiationEvent(const JsonObject& parameters) {
  string message;
  parameters.ToString(message);
  printf("%s : %s\n", __FUNCTION__, message.c_str());
}

void ThunderClient::onArcTerminationEvent(const JsonObject& parameters) {
  string message;
  parameters.ToString(message);
  printf("%s : %s\n", __FUNCTION__, message.c_str());
}

void ThunderClient::onShortAudiodesciptorEvent(const JsonObject& parameters) {
  string message;
  parameters.ToString(message);
  printf("%s : %s\n", __FUNCTION__, message.c_str());
}
