#ifndef BINARY_SEMAPHORE_H
#define BINARY_SEMAPHORE_H

class BinarySemaphore {
public:
  class Lock {
  public:
    Lock() = delete;
    Lock(const Lock &) = delete;
    Lock &operator=(const Lock &) = delete;
    Lock(BinarySemaphore* sem);
    ~Lock();
  private:
    BinarySemaphore* ptr;
    bool locked;
  };
  BinarySemaphore();
  BinarySemaphore(const BinarySemaphore &) = delete;
  BinarySemaphore &operator=(const BinarySemaphore &) = delete;
  ~BinarySemaphore();
  bool Wait();
  bool Unlock();
private:
  int fd_lock;
};

#endif //BINARY_SEMAPHORE_H
