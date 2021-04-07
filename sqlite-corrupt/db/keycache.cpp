#include "keycache.h"

using namespace std;

KeyCache& KeyCache::instance() {
  static KeyCache i;
  return i;
}

string KeyCache::generate() {
  return to_string(mAutoIncrement++);
}

string KeyCache::getAny() {
  string result;
  lock_guard<mutex> lck(mLock);
  int num = mKeys.size();
  if (num > 0) {
    auto it = mKeys.begin();
    if (num > 1) {
      std::advance(it, (std::rand() % num));
    }
    return (*it);
  }
  return result;
}

void KeyCache::write(const string& key) {
  lock_guard<mutex> lck(mLock);
  mKeys.emplace(key);
}

void KeyCache::remove(const string& key) {
  lock_guard<mutex> lck(mLock);
  mKeys.erase(mKeys.find(key), mKeys.end());
}

void KeyCache::clear() {
  lock_guard<mutex> lck(mLock);
  mKeys.clear();
}
