#include "writer.h"

#include "db/dbholder.h"
#include "db/keycache.h"

#include <functional>

using namespace std;

void Writer::activate() {
  deactivate();

  mActive = true;
  mThread = std::thread(std::bind(&Writer::threadRun, this));
}

void Writer::deactivate() {
  mActive = false;
  if (mThread.joinable())
    mThread.join();
}

void Writer::threadRun() {
  while (mActive) {
    string key = KeyCache::instance().generate();

    bool ret = DbHolder::instance().db().write(key, "12345");
    printf("write '%s' - %s\n", key.c_str(), ret ? "success" : "failure");

    if (ret)
      KeyCache::instance().write(key);

    std::this_thread::sleep_for(std::chrono::milliseconds(mInterval));
  }
}
