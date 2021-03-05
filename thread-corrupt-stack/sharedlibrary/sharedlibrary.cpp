#include "sharedlibrary.h"

#include <chrono>
#include <thread>

static bool isThreadRunning = false;

class SharedLibraryImp : public ISharedLibraryImp {
public:
  SharedLibraryImp() = default;
  ~SharedLibraryImp();

  void startThread() noexcept;

private:
  static void threadRun();

  std::thread m_thread;
};

SharedLibraryImp::~SharedLibraryImp() {
#ifdef JOIN_THREAD_ON_EXIT
  isThreadRunning = false;

  if (m_thread.joinable())
    m_thread.join();
#endif
}

void SharedLibraryImp::startThread() noexcept {
  isThreadRunning = true;

  m_thread = std::thread(threadRun);
}

void SharedLibraryImp::threadRun() {
  while (1) {
    if (!isThreadRunning) {
      printf("Thread Exit\n");
      break;
    }

    printf("Thread Run\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

extern "C" {
void create(std::shared_ptr<ISharedLibraryImp>& ptr) {
  ptr.reset(new SharedLibraryImp);
}
} // extern "C"
