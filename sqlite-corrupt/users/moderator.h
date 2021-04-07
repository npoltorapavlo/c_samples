#ifndef C_SAMPLES_MODERATOR_H
#define C_SAMPLES_MODERATOR_H

#include "user.h"

#include <thread>

class Moderator : public User {
public:
  Moderator(uint32_t interval) : mInterval(interval), mActive(false) {}
  virtual ~Moderator() { deactivate(); }

  void activate();
  void deactivate();

private:
  Moderator(const Moderator&) = delete;
  Moderator& operator=(const Moderator&) = delete;

  void threadRun();

private:
  uint32_t mInterval;
  std::thread mThread;
  bool mActive;
};

#endif //C_SAMPLES_MODERATOR_H
