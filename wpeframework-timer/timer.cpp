#include "timer.h"

using namespace std;
using namespace WPEFramework;

Timer::Timer() :
    baseTimer(64 * 1024, "TestTimer")
    , m_timerJob(this)
    , m_isActive(false)
    , m_isSingleShot(false)
    , m_intervalInMs(-1)
{}

Timer::~Timer() {
  stop();
}

bool Timer::isActive() {
  return m_isActive;
}

void Timer::stop() {
  baseTimer.Revoke(m_timerJob);
  m_isActive = false;
}

void Timer::start() {
  baseTimer.Revoke(m_timerJob);
  baseTimer.Schedule(Core::Time::Now().Add(m_intervalInMs), m_timerJob);
  m_isActive = true;
}

void Timer::start(int msec) {
  setInterval(msec);
  start();
}

void Timer::setSingleShot(bool val) {
  m_isSingleShot = val;
}

void Timer::setInterval(int msec) {
  m_intervalInMs = msec;
}

void Timer::connect(std::function< void() > callback) {
  onTimeoutCallback = callback;
}

void Timer::Timed() {
  if (onTimeoutCallback != nullptr) {
    onTimeoutCallback();
  }

  if (m_isActive) {
    if (m_isSingleShot) {
      stop();
    } else {
      start();
    }
  }
}

uint64_t TimerJob::Timed(const uint64_t scheduledTime) {
  if (m_timer) {
    m_timer->Timed();
  }
  return 0;
}
