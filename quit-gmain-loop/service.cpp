#include "service.h"

#include <algorithm>
#include <cstring>
#include <cstdio>

ServiceAdmin ServiceAdmin::_serviceAdmin;

void ServiceAdmin::Register(IService* service) {
  _services.push_back(service);
}

void ServiceAdmin::Unregister(IService* service) {
  std::list<IService *>::iterator index = std::find(_services.begin(), _services.end(), service);
  _services.erase(index);
}

ServiceAdmin& ServiceAdmin::Instance() {
  return (_serviceAdmin);
}

void* ServiceAdmin::Instantiate(const char name[]) {
  std::list<IService *>::iterator index = std::find_if(
      _services.begin(), _services.end(),
      [&name](const IService *x) { return (strcmp(x->Name(), name) == 0); });

  if (index == _services.end()) {
    printf("Missing implementation %s\n", name);
  }

  return (index != _services.end() ? (*index)->Create() : nullptr);
}
