#include "sharedlibrary.h"

#include <pthread.h>
#include <unistd.h>

bool isRunning = false;

class SharedLibraryImp : public ISharedLibraryImp {
public:
  SharedLibraryImp() = default;
  ~SharedLibraryImp();

  void startThread() noexcept;
  static bool isThreadRunning() { return isRunning; };

private:
  static void *threadRun(void *);

  pthread_t thread;
};

SharedLibraryImp::~SharedLibraryImp() {
  printf("%s\n", __FUNCTION__);
#ifdef JOIN_THREAD_ON_EXIT
  isRunning = false;

  pthread_join(thread, nullptr);
#endif
}

void SharedLibraryImp::startThread() noexcept {
  isRunning = true;

  int rc = pthread_create(&thread, nullptr, (void* (*)(void*))threadRun, nullptr);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
  }
}

void *SharedLibraryImp::threadRun(void *) {
  while (isRunning) {
    usleep(1);
  }
  printf("%s done\n", __FUNCTION__);
  return nullptr;
}

extern "C" {
void create(std::shared_ptr<ISharedLibraryImp>& ptr) {
  ptr.reset(new SharedLibraryImp);
}
} // extern "C"
