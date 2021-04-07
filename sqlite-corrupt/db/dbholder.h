#ifndef C_SAMPLES_DBHOLDER_H
#define C_SAMPLES_DBHOLDER_H

#include "db.h"

class DbHolder {
public:
  static DbHolder& instance();

  Db& db() { return mDb; }

  bool destroy();

private:
  DbHolder() = default;
  ~DbHolder() = default;
  DbHolder(const DbHolder&) = delete;
  DbHolder& operator=(const DbHolder&) = delete;

private:
  Db mDb;
};

#endif //C_SAMPLES_DBHOLDER_H
