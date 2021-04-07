#include "moderator.h"

#include "db/dbholder.h"
#include "db/keycache.h"

#include <chrono>
#include <functional>

using namespace std;

void Moderator::activate() {
  deactivate();

  mActive = true;
  mThread = std::thread(std::bind(&Moderator::threadRun, this));
}

void Moderator::deactivate() {
  mActive = false;
  if (mThread.joinable())
    mThread.join();
}

void Moderator::threadRun() {
  while (mActive) {
    string key = KeyCache::instance().getAny();
    if (!key.empty()) {
      bool ret = DbHolder::instance().db().remove(key);
      printf("remove '%s' - %s\n", key.c_str(), ret ? "success" : "failure");

      if (ret)
        KeyCache::instance().remove(key);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(mInterval));
  }
}
