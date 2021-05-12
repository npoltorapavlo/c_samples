#ifndef C_SAMPLES_PERFORMANCECOUNT_H
#define C_SAMPLES_PERFORMANCECOUNT_H

#include <atomic>
#include <chrono>
#include <string>

class PerformanceCount {
public:
  class Iteration {
  public:
    Iteration(PerformanceCount* parent);
    ~Iteration();

  private:
    PerformanceCount* mparent;
    std::chrono::time_point<std::chrono::steady_clock> mstart;
  };

  PerformanceCount(const std::string& id);
  ~PerformanceCount();

  void addTime(long time);

private:
  std::string mid;
  std::atomic<long> mtime;
  std::atomic<long> mcount;
};

#endif //C_SAMPLES_PERFORMANCECOUNT_H
