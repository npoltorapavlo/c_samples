#include "fileutils.h"

#include <sys/stat.h>
#include <cstdio>

namespace FileUtils {

bool fileRemove(const char* path) {
  return (remove (path) == 0);
}

bool fileExists(const char* path) {
  struct stat buffer;
  return (stat (path, &buffer) == 0);
}

} // namespace FileUtils
