#include "critsection.h"

#include "binarysemaphore.h"

#include <unistd.h>
#include <thread>
#include <chrono>

void critSection(const uint32_t waitTime, const uint32_t runTimeS) {
  printf("entering crit section pid %ld\n", (long) getpid());

  BinarySemaphore sem("critSection");
  BinarySemaphore::Lock lock(&sem, waitTime);

  printf("entered crit section pid %ld\n", (long) getpid());

  std::this_thread::sleep_for(std::chrono::seconds(runTimeS));

  printf("leaving crit section pid %ld\n", (long) getpid());
}
