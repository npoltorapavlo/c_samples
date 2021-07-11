#include "client.h"

#include <core/core.h>
#include <com/com.h>
#include <plugins/plugins.h>

using namespace WPEFramework;

bool GetToken(unsigned short maxLength, unsigned short inLength, unsigned char buffer[]) {
  bool result = false;

  static const string endPoint = _T("/tmp/token_test");

  auto engine = Core::ProxyType < RPC::InvokeServerType <1, 0, 4 >> ::Create();
  auto client = Core::ProxyType<RPC::CommunicatorClient>::Create(Core::NodeId(endPoint.c_str()),
                                                                 Core::ProxyType<Core::IIPCServer>(engine));

  if ((client.IsValid() == true) && (client->IsOpen() == false)) {
    PluginHost::IAuthenticate *interface = client->Open<PluginHost::IAuthenticate>("Authenticator");

    if (interface != nullptr) {
      std::string token;
      uint32_t error = interface->CreateToken(inLength, buffer, token);
      if (error == Core::ERROR_NONE) {
        if (token.length() <= maxLength) {
          std::copy(std::begin(token), std::end(token), buffer);
          result = true;
        } else {
          printf("token exceeds maxLength\n", __FILE__, __LINE__, __func__);
        }
      }
      interface->Release();
    }

    client.Release();
  } else {
    printf("could not open client\n", __FILE__, __LINE__, __func__);
  }

  return result;
}
