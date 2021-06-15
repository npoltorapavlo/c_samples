#include "semaphore.h"

#include <fcntl.h>
#include <time.h>

Semaphore::Lock::Lock(Semaphore* sem, const uint32_t waitTime)
  : ptr(sem)
  , locked(false) {
  locked = ptr->Wait(waitTime);
}

Semaphore::Lock::~Lock() {
  if (locked) {
    ptr->Unlock();
  }
}

Semaphore::Semaphore(const char* name)
  : sem(nullptr)
  , sem_name(name) {
  if ((sem = sem_open(sem_name.c_str(), O_CREAT, 0644, 1)) == SEM_FAILED) {
    printf("%s:%d [%s] sem_open %d\n", __FILE__, __LINE__, __func__, errno);
  }
}

Semaphore::~Semaphore() {
  if (sem_unlink(sem_name.c_str()) == -1) {
    if (errno != ENOENT) {
      printf("%s:%d [%s] sem_unlink %d\n", __FILE__, __LINE__, __func__, errno);
    }
  }
}

bool Semaphore::Wait(const uint32_t waitTime) {
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

bool Semaphore::Unlock() {
  bool result = false;
  if (sem_post(sem) == -1) {
    printf("%s:%d [%s] sem_post %d\n", __FILE__, __LINE__, __func__, errno);
  } else {
    result = true;
  }
  return result;
}
