#include "server.h"

#include <functional>

namespace WPEFramework {

void *Authenticator::Provider::Aquire(const string &, const uint32_t interfaceId, const uint32_t versionId) {
  void *result = nullptr;
  if (((versionId == 1) || (versionId == static_cast<uint32_t>(~0))) &&
      ((interfaceId == PluginHost::IAuthenticate::ID) || (interfaceId == Core::IUnknown::ID))) {
    _parentInterface->AddRef();
    printf("interface(IAuthenticate) acquired\n");
    result = _parentInterface;
  }
  return (result);
}

Authenticator::Provider::Provider(const Core::NodeId &source, PluginHost::IAuthenticate *parentInterface,
  const Core::ProxyType <InvokeServer> &engine)
  : RPC::Communicator(source, _T(""), Core::ProxyType<Core::IIPCServer>(engine)),
  _parentInterface(parentInterface) {
  printf("interface(IAuthenticate) constructor\n");
  engine->Announcements(Announcement());
  Open(Core::infinite);
}

Authenticator::Provider::~Provider() {
  printf("interface(IAuthenticate) destructor\n");
  Close(Core::infinite);
}

Authenticator::Authenticator()
  : _provider(nullptr)
  , _engine() {
  string connector = _T("/tmp/token_test");

  _engine = Core::ProxyType<RPC::InvokeServer>::Create(&Core::IWorkerPool::Instance());
  _provider.reset(new Provider(Core::NodeId(connector.c_str()), this, _engine));

  if (_provider != nullptr) {
    if (_provider->IsListening() == false) {
      _provider.reset(nullptr);
      _engine.Release();
    } else {
      printf("interface(IAuthenticate) providing\n");
    }
  }
}

uint32_t Authenticator::CreateToken(const uint16_t length, const uint8_t buffer[], string& token) {
  printf("interface(IAuthenticate) CreateToken called\n");

  string str(buffer, length);
  size_t str_hash = hash<string>{}(str);
  token = to_string(str_hash);

  return Core::ERROR_NONE;
}

PluginHost::ISecurity* Authenticator::Officer(const string& token) {
  printf("interface(IAuthenticate) Officer called\n");
  return nullptr;
}

} // namespace WPEFramework
