#ifndef C_SAMPLES_THUNDERCONTROLLER_H
#define C_SAMPLES_THUNDERCONTROLLER_H

#include <core/core.h>
#include <websocket/websocket.h>

#include <memory>

class ThunderController {
public:
  ThunderController() = default;

  ~ThunderController() = default;

  void Init();

  bool Activate(const char *callSign);

  bool IsActivated(const char *callSign);

private:
  std::shared_ptr <WPEFramework::JSONRPC::LinkType<WPEFramework::Core::JSON::IElement>> m_thunderClient;
};

#endif //C_SAMPLES_THUNDERCONTROLLER_H
