#include "dbholder.h"

#include "fileutils.h"

DbHolder& DbHolder::instance() {
  static DbHolder i;
  return i;
}

bool DbHolder::destroy() {
  return FileUtils::fileRemove(Db::FILENAME);
}
