#include "critsection.h"

#include "semaphore.h"

#include <unistd.h>
#include <thread>
#include <chrono>

void critSection(const uint32_t waitTime, const uint32_t runTimeS) {
  printf("entering crit section pid %ld\n", (long) getpid());

  static Semaphore mutex("critSection");
  Semaphore::Lock lock(&mutex, waitTime);

  printf("entered crit section pid %ld\n", (long) getpid());

  std::this_thread::sleep_for(std::chrono::seconds(runTimeS));

  printf("leaving crit section pid %ld\n", (long) getpid());
}
