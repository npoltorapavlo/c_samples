#ifndef C_SAMPLES_SLEEPINTERRUPT_H
#define C_SAMPLES_SLEEPINTERRUPT_H

#include <mutex>
#include <chrono>
#include <condition_variable>

class SleepInterrupt {
public:
  SleepInterrupt() : interrupt(false) {}
  ~SleepInterrupt() { interrupt(); }

  template <typename Rep, typename Period>
  void sleep_for(const std::chrono::duration<Rep,Period>& rel_time) {
    std::unique_lock<std::mutex> lock(mutex);
    cond.wait_for(lock, rel_time, [this] { return this->interrupt; });
    interrupt = false;
  }

  void interrupt() {
    std::unique_lock<std::mutex> lock(mutex);
    interrupt = true;
    lock.unlock();
    cond.notify_one();
  }

private:
  bool interrupt;
  std::mutex mutex;
  std::condition_variable cond;
};

#endif //C_SAMPLES_SLEEPINTERRUPT_H
