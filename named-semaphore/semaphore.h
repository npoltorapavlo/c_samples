#ifndef CLIENTLIBRARIES_SEMAPHORE_H
#define CLIENTLIBRARIES_SEMAPHORE_H

#include <semaphore.h>
#include <string>

class Semaphore {
public:
  class Lock {
  public:
    Lock() = delete;
    Lock(const Lock &) = delete;
    Lock &operator=(const Lock &) = delete;
    Lock(Semaphore* sem, const uint32_t waitTime);
    ~Lock();
  private:
    Semaphore* ptr;
    bool locked;
  };
  Semaphore() = delete;
  Semaphore(const Semaphore &) = delete;
  Semaphore &operator=(const Semaphore &) = delete;
  Semaphore(const char *name);
  ~Semaphore();
  bool Wait(const uint32_t waitTime);
  bool Unlock();
private:
  sem_t *sem;
  std::string sem_name;
};

#endif //CLIENTLIBRARIES_SEMAPHORE_H
