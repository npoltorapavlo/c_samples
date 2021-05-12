#include "performancecount.h"

using namespace std;

PerformanceCount::Iteration::Iteration(PerformanceCount* parent)
: mparent(parent)
, mstart(chrono::steady_clock::now()) {
}

PerformanceCount::Iteration::~Iteration() {
  mparent->addTime(chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - mstart).count());
}

PerformanceCount::PerformanceCount(const std::string& id)
: mid(id), mtime(0), mcount(0) {
}

PerformanceCount::~PerformanceCount() {
  printf("%s, time=%ld (microseconds), count=%ld\n", mid.c_str(), (long)mtime, (long)mcount);
}

void PerformanceCount::addTime(long time) {
  mtime += time;
  mcount++;
}
