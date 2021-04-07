#ifndef C_SAMPLES_CLEANER_H
#define C_SAMPLES_CLEANER_H

#include "user.h"

#include <thread>

class Cleaner : public User {
public:
  Cleaner(uint32_t interval) : mInterval(interval), mActive(false) {}
  virtual ~Cleaner() { deactivate(); }

  void activate();
  void deactivate();

private:
  Cleaner(const Cleaner&) = delete;
  Cleaner& operator=(const Cleaner&) = delete;

  void threadRun();

private:
  uint32_t mInterval;
  std::thread mThread;
  bool mActive;
};

#endif //C_SAMPLES_CLEANER_H
