#ifndef C_SAMPLES_SERVER_H
#define C_SAMPLES_SERVER_H

#include <core/core.h>
#include <com/com.h>
#include <plugins/plugins.h>

namespace WPEFramework {

class Authenticator : public PluginHost::IAuthenticate {
private:
  class Provider : public RPC::Communicator {
  public:
    Provider() = delete;
    Provider(const Core::NodeId &source, PluginHost::IAuthenticate *parentInterface,
             const Core::ProxyType <RPC::InvokeServer> &engine);
    ~Provider() override;

  private:
    void *Aquire(const string &, const uint32_t interfaceId, const uint32_t versionId) override;

    PluginHost::IAuthenticate *_parentInterface;
  };

public:
  Authenticator(const Authenticator &) = delete;
  Authenticator &operator=(const Authenticator &) = delete;
  Authenticator();
  virtual ~Authenticator();

  BEGIN_INTERFACE_MAP(Authenticator)
  INTERFACE_ENTRY(PluginHost::IAuthenticate)
  END_INTERFACE_MAP

public:
  virtual uint32_t CreateToken(const uint16_t length, const uint8_t buffer[], string &token);
  virtual PluginHost::ISecurity *Officer(const string &token);

private:
  std::unique_ptr<Provider> _provider;
  Core::ProxyType<RPC::InvokeServer> _engine;
};

} // namespace WPEFramework
        
#endif //C_SAMPLES_SERVER_H
