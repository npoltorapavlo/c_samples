#ifndef BINARY_SEMAPHORE_H
#define BINARY_SEMAPHORE_H

#include <semaphore.h>
#include <string>

class BinarySemaphore {
public:
  class Lock {
  public:
    Lock() = delete;
    Lock(const Lock &) = delete;
    Lock &operator=(const Lock &) = delete;
    Lock(BinarySemaphore* sem, const uint32_t waitTime);
    ~Lock();
  private:
    BinarySemaphore* ptr;
    bool locked;
  };
  BinarySemaphore() = delete;
  BinarySemaphore(const BinarySemaphore &) = delete;
  BinarySemaphore &operator=(const BinarySemaphore &) = delete;
  BinarySemaphore(const char *name);
  ~BinarySemaphore();
  bool Wait(const uint32_t waitTime);
  bool Unlock();
private:
  sem_t *sem;
  std::string sem_name;
};

#endif //BINARY_SEMAPHORE_H
