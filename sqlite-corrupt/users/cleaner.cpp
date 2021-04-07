#include "cleaner.h"

#include "db/dbholder.h"
#include "db/keycache.h"

#include <chrono>
#include <functional>

using namespace std;

void Cleaner::activate() {
  deactivate();

  mActive = true;
  mThread = std::thread(std::bind(&Cleaner::threadRun, this));
}

void Cleaner::deactivate() {
  mActive = false;
  if (mThread.joinable())
    mThread.join();
}

void Cleaner::threadRun() {
  while (mActive) {
    bool ret = DbHolder::instance().destroy();
    printf("clean - %s\n", ret ? "success" : "failure");

    if (ret)
      KeyCache::instance().clear();

    std::this_thread::sleep_for(std::chrono::milliseconds(mInterval));
  }
}
