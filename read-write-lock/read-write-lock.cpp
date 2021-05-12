#include "performancecount.h"
#include "keyholder.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <cassert>

using namespace std;

mutex mtx;
atomic<int> reading(0);

KeyHolder key;
PerformanceCount writes("writes");
PerformanceCount reads("reads");

void write() {
  PerformanceCount::Iteration perf(&writes);

#ifdef READ_WRITE_LOCK
  lock_guard<mutex> lck(mtx);
#elif ADVANCED_LOCK
  lock_guard<mutex> lck(mtx);
  while (reading > 0);
#endif

  key.write((long)rand() * 100l);
}

void read() {
  PerformanceCount::Iteration perf(&reads);

#ifdef READ_WRITE_LOCK
  lock_guard<mutex> lck(mtx);
#elif ADVANCED_LOCK
  {
    lock_guard<mutex> lck(mtx);
    reading++;
  }
#endif

  if (!key.empty()) {
    assert((key.read() % 100l) == 0);
  }

#ifdef ADVANCED_LOCK
  reading--;
#endif
}

int main(int argc, char** argv) {
  srand(time(nullptr));

  atomic<bool> running(true);

  thread w1([&] { while(running) write(); });
  thread w2([&] { while(running) write(); });
  thread r1([&] { while(running) read(); });
  thread r2([&] { while(running) read(); });

  std::this_thread::sleep_for(std::chrono::seconds(20));

  running = false;

  w1.join();
  w2.join();
  r1.join();
  r2.join();

  return 0;
}
