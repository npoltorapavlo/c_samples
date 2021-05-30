#ifndef C_SAMPLES_SERVICE_H
#define C_SAMPLES_SERVICE_H

#include <list>

#define TCHAR char

struct IService {
  virtual ~IService() {};
  virtual const TCHAR* Name() const = 0;
  virtual void *Create() = 0;
};

class ServiceAdmin {
private:
  ServiceAdmin(const ServiceAdmin &) = delete;
  ServiceAdmin &operator=(const ServiceAdmin &) = delete;

public:
  ServiceAdmin() = default;
  ~ServiceAdmin() = default;

  void Register(IService *service);
  void Unregister(IService *service);

  void *Instantiate(const char name[]);

  template<typename INTERFACE>
  INTERFACE *Instantiate(const char name[]) {
    void *baseInterface(Instantiate(name));

    if (baseInterface != nullptr) {
      return (reinterpret_cast<INTERFACE *>(baseInterface));
    }

    return (nullptr);
  }

  static ServiceAdmin &Instance();

private:
  std::list<IService*> _services;
  static ServiceAdmin _serviceAdmin;
};

template <typename SERVICE, const TCHAR** NAME>
class Service : public IService {
public:
  Service(int version) : _version(version) {
    ServiceAdmin::Instance().Register(this);
  }

  ~Service() {
    ServiceAdmin::Instance().Unregister(this);
  }

  int Version() {
    return _version;
  }

public:
  virtual const TCHAR *Name() const {
    return (*NAME);
  }

  virtual void *Create() {
    return (new SERVICE());
  }

private:
  int _version;
};

#define SERVICE_REGISTER(CLASS, VERSION) \
    const char* ServiceName_##CLASS = #CLASS; \
    static Service<CLASS, &ServiceName_##CLASS> Service_##CLASS(VERSION);

#endif //C_SAMPLES_SERVICE_H
