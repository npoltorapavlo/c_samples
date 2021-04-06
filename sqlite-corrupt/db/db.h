#ifndef C_SAMPLES_DB_H
#define C_SAMPLES_DB_H

#include <mutex>

class Db {
public:
  Db();
  virtual ~Db();

  static const char* FILENAME;

  bool write(const std::string& key, const std::string& value);
  bool read(const std::string& key, std::string& value);
  bool remove(const std::string& key);
  bool open();
  void term();

private:
  Db(const Db&) = delete;
  Db& operator=(const Db&) = delete;

private:
  void* mData;
  std::mutex mLock;
};

#endif //C_SAMPLES_DB_H
