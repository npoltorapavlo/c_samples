#include "binarysemaphore.h"

#include <sys/file.h>
#include <cerrno>
#include <cstdio>
#include <unistd.h>
#include <string.h>

BinarySemaphore::Lock::Lock(BinarySemaphore* sem)
  : ptr(sem)
  , locked(false) {
  locked = ptr->Wait();
}

BinarySemaphore::Lock::~Lock() {
  if (locked) {
    ptr->Unlock();
  }
}

BinarySemaphore::BinarySemaphore() {
  if ((fd_lock = open("/tmp/.lockfile", O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
    printf("%s:%d [%s] open %d (%s)\n", __FILE__, __LINE__, __func__, errno, strerror(errno));
  }
}

BinarySemaphore::~BinarySemaphore() {
  if (close(fd_lock) != 0) {
    printf("%s:%d [%s] close %d (%s)\n", __FILE__, __LINE__, __func__, errno, strerror(errno));
  }
}

bool BinarySemaphore::Wait() {
  bool result = false;
  if (flock(fd_lock, LOCK_EX) != 0) {
    printf("%s:%d [%s] flock %d (%s)\n", __FILE__, __LINE__, __func__, errno, strerror(errno));
  } else {
    result = true;
  }
  return result;
}

bool BinarySemaphore::Unlock() {
  bool result = false;
  if (flock(fd_lock, LOCK_UN) != 0) {
    printf("%s:%d [%s] flock %d (%s)\n", __FILE__, __LINE__, __func__, errno, strerror(errno));
  } else {
    result = true;
  }
  return result;
}
