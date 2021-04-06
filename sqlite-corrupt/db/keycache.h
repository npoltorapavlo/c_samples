#ifndef C_SAMPLES_KEYCACHE_H
#define C_SAMPLES_KEYCACHE_H

#include <string>
#include <atomic>
#include <mutex>
#include <set>

class KeyCache {
public:
  static KeyCache& instance();

  std::string generate();
  std::string getAny();
  void write(const std::string& key);
  void remove(const std::string& key);
  void clear();

private:
  KeyCache() : mAutoIncrement(0) {}
  ~KeyCache() = default;
  KeyCache(const KeyCache&) = delete;
  KeyCache& operator=(const KeyCache&) = delete;

private:
  std::set<std::string> mKeys;
  std::atomic<uint32_t> mAutoIncrement;
  std::mutex mLock;
};

#endif //C_SAMPLES_KEYCACHE_H
