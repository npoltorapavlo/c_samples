#include "critsection.h"

#include "binarysemaphore.h"

#include <unistd.h>
#include <thread>
#include <chrono>

int main(int argc, char** argv) {
  printf("starting pid %ld\n", (long) getpid());

  pid_t pid = fork();
  if (pid == 0) {
    printf("forked child process pid %ld\n", (long) getpid());
    BinarySemaphore sem;
    sem.Wait();
    printf("child process acquired lock, forcing segfault\n");
    *(int*)0 = 0;
    printf("can't be here\n");
  } else {
    printf("parent process pid %ld waits\n", (long) getpid());
    std::this_thread::sleep_for(std::chrono::seconds(1));
    BinarySemaphore sem;
    sem.Wait();
    printf("parent process acquired lock, test paased!!!\n");
  }

  printf("ending pid %ld\n", (long) getpid());

  return 0;
}
