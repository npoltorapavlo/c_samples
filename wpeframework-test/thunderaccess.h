#ifndef C_SAMPLES_THUNDERACCESS_H_
#define C_SAMPLES_THUNDERACCESS_H_

#include <core/core.h>
#include <websocket/websocket.h>

class ThunderAccess {
public:
  ThunderAccess(const std::string &callsign);

  ~ThunderAccess();

  // 0 == Core::ERROR_NONE
  uint32_t ActivatePlugin();
  uint32_t InvokeJSONRPC(const std::string &method, const JsonObject &param, JsonObject &result);
  uint32_t SubscribeEvent(const std::string &eventName,
                          std::function<void(const WPEFramework::Core::JSON::VariantContainer &)> functionHandler);

  void UnSubscribeEvent(const std::string &eventName);

  uint32_t Get(const std::string &method, JsonObject &result);

private:
  WPEFramework::JSONRPC::LinkType <WPEFramework::Core::JSON::IElement> *remoteObject;
  WPEFramework::JSONRPC::LinkType <WPEFramework::Core::JSON::IElement> *controllerObject;

  std::string pluginCallsign;
};

#endif // C_SAMPLES_THUNDERACCESS_H_
