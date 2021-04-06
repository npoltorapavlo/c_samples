#ifndef C_SAMPLES_READER_H
#define C_SAMPLES_READER_H

#include "user.h"

#include <thread>

class Reader : public User {
public:
  Reader(uint32_t interval) : mInterval(interval), mActive(false) {}
  virtual ~Reader() { deactivate(); }

  void activate();
  void deactivate();

private:
  Reader(const Reader&) = delete;
  Reader& operator=(const Reader&) = delete;

  void threadRun();

private:
  uint32_t mInterval;
  std::thread mThread;
  bool mActive;
};

#endif //C_SAMPLES_READER_H
