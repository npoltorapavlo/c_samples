#include "reader.h"

#include "db/dbholder.h"
#include "db/keycache.h"

#include <functional>

using namespace std;

void Reader::activate() {
  deactivate();

  mActive = true;
  mThread = std::thread(std::bind(&Reader::threadRun, this));
}

void Reader::deactivate() {
  mActive = false;
  if (mThread.joinable())
    mThread.join();
}

void Reader::threadRun() {
  while (mActive) {
    string key = KeyCache::instance().getAny();
    if (!key.empty()) {
      string val;
      bool ret = DbHolder::instance().db().read(key, val);
      printf("read '%s' '%s' - %s\n", key.c_str(), val.c_str(), ret ? "success" : "failure");
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(mInterval));
  }
}
