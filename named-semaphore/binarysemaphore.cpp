#include "binarysemaphore.h"

#include <fcntl.h>
#include <time.h>

BinarySemaphore::Lock::Lock(BinarySemaphore* sem, const uint32_t waitTime)
  : ptr(sem)
  , locked(false) {
  locked = ptr->Wait(waitTime);
}

BinarySemaphore::Lock::~Lock() {
  if (locked) {
    ptr->Unlock();
  }
}

BinarySemaphore::BinarySemaphore(const char* name)
  : sem(nullptr)
  , sem_name(name) {
  if ((sem = sem_open(sem_name.c_str(), O_CREAT, 0644, 1)) == SEM_FAILED) {
    printf("%s:%d [%s] sem_open %d\n", __FILE__, __LINE__, __func__, errno);
  }
}

BinarySemaphore::~BinarySemaphore() {
  if (sem_close(sem) == -1) {
    printf("%s:%d [%s] sem_close %d\n", __FILE__, __LINE__, __func__, errno);
  }
}

bool BinarySemaphore::Wait(const uint32_t waitTime) {
  bool result = false;
  struct timespec ts;
  if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
    printf("%s:%d [%s] clock_gettime %d\n", __FILE__, __LINE__, __func__, errno);
  } else {
    ts.tv_sec += waitTime;
    do {
      if (sem_timedwait(sem, &ts) == -1) {
        if (errno == EINTR)
          continue;
        printf("%s:%d [%s] sem_timedwait %d\n", __FILE__, __LINE__, __func__, errno);
      } else {
        result = true;
      }
      break;
    } while (true);
  }
  return result;
}

bool BinarySemaphore::Unlock() {
  bool result = false;
  if (sem_post(sem) == -1) {
    printf("%s:%d [%s] sem_post %d\n", __FILE__, __LINE__, __func__, errno);
  } else {
    result = true;
  }
  return result;
}
