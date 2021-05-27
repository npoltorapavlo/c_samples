#ifndef C_SAMPLES_TIMER_H
#define C_SAMPLES_TIMER_H

#include <plugins/plugins.h>

class Timer;

class TimerJob {
private:
  TimerJob() = delete;

  TimerJob &operator=(const TimerJob &RHS) = delete;

public:
  TimerJob(Timer *t) : m_timer(t) {}

  TimerJob(const TimerJob &copy) : m_timer(copy.m_timer) {}

  ~TimerJob() {}

  inline bool operator==(const TimerJob &RHS) const {
    return (m_timer == RHS.m_timer);
  }

public:
  uint64_t Timed(const uint64_t scheduledTime);

private:
  Timer *m_timer;
};

class Timer {
public:
  Timer();

  ~Timer();

  bool isActive();

  void stop();

  void start();

  void start(int msec);

  void setSingleShot(bool val);

  void setInterval(int msec);

  void connect(std::function<void()> callback);

private:

  void Timed();

  WPEFramework::Core::TimerType <TimerJob> baseTimer;
  TimerJob m_timerJob;
  bool m_isActive;
  bool m_isSingleShot;
  int m_intervalInMs;

  std::function<void()> onTimeoutCallback;

  friend class TimerJob;
};

#endif
