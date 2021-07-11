#include "authclient.h"

#include "Module.h"

using namespace WPEFramework;

bool TestAuth(const std::string& endpoint, const std::string& name) {
  bool result = false;

  printf("%s (%s, %s)\n", __func__, endpoint.c_str(), name.c_str());

  auto engine = Core::ProxyType<RPC::InvokeServerType<1, 0, 4>>::Create();
  auto client = Core::ProxyType<RPC::CommunicatorClient>::Create(
      Core::NodeId(endpoint.c_str()),
      Core::ProxyType<Core::IIPCServer>(engine));

  if ((client.IsValid() == true) && (client->IsOpen() == false)) {
    PluginHost::IAuthenticate *interface =
        client->Open<PluginHost::IAuthenticate>(name);

    if (interface != nullptr) {
      const uint8_t buffer[] = "https://www.google.com";
      std::string token;
      uint32_t error = interface->CreateToken(strlen((const char*)buffer), buffer, token);
      if (error == Core::ERROR_NONE) {
        printf("%s success : %s\n", __func__, token.c_str());
        result = true;
      } else {
        printf("%s error : %u\n", __func__, error);
      }

      interface->Release();
    } else {
      printf("%s Open is null\n", __func__);
    }

    client.Release();
  } else {
    printf("%s IsValid/IsOpen is false\n", __func__);
  }

  return result;
}
