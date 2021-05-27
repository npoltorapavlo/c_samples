#pragma once

#include <core/core.h>
#include <websocket/websocket.h>

#include "timer.h"
#include "thundercontroller.h"

#include <mutex>
#include <memory>

class ThunderClient {
public:
  ThunderClient();
  ~ThunderClient();

  void Init();
  void DeInit();

private:
  typedef void (ThunderClient::*ThunderClientEventHandler)(const JsonObject&);

  void onArcInitiationEvent(const JsonObject& parameters);
  void onArcTerminationEvent(const JsonObject& parameters);
  void onShortAudiodesciptorEvent(const JsonObject& parameters);
  bool subscribeForEvent(const char* eventName, const ThunderClientEventHandler& method);
  void onTimer();

private:
  Timer m_timer;
  bool m_subscribed;
  std::mutex m_callMutex;
  std::shared_ptr<WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement> > m_client;
  ThunderController m_thunderController;
};
