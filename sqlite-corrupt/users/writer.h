#ifndef C_SAMPLES_WRITER_H
#define C_SAMPLES_WRITER_H

#include "user.h"

#include <thread>

class Writer : public User {
public:
  Writer(uint32_t interval) : mInterval(interval), mActive(false) {}
  virtual ~Writer() { deactivate(); }

  void activate();
  void deactivate();

private:
  Writer(const Writer&) = delete;
  Writer& operator=(const Writer&) = delete;

  void threadRun();

private:
  uint32_t mInterval;
  std::thread mThread;
  bool mActive;
};

#endif //C_SAMPLES_WRITER_H
