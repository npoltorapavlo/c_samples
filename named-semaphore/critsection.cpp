#include "critsection.h"

#include "binarysemaphore.h"

#include <unistd.h>
#include <thread>
#include <chrono>

void critSection() {
  printf("entering crit section pid %ld\n", (long) getpid());

  BinarySemaphore sem("critSection");
  BinarySemaphore::Lock lock(&sem, 10);

  printf("entered crit section pid %ld\n", (long) getpid());

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  printf("leaving crit section pid %ld\n", (long) getpid());
}
