#include "critsection.h"

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

int main(int argc, char** argv) {
  int numForks = ((argc > 1) ? atoi(argv[1]) : 3);
  int programRun = ((argc > 2) ? atoi(argv[2]) : 10);
  int semWait = ((argc > 3) ? atoi(argv[3]) : 5);
  int critSectionRun = ((argc > 4) ? atoi(argv[4]) : 1);

  printf("starting pid %ld numForks=%d, programRun=%d, semWait=%d, critSectionRun=%d\n",
         (long) getpid(), numForks, programRun, semWait, critSectionRun);

  for (int i = 0; i < numForks; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      printf("forked child process pid %ld\n", (long) getpid());
      critSection(semWait, critSectionRun);
      break;
    }
  }

  std::this_thread::sleep_for(std::chrono::seconds(programRun));

  printf("ending pid %ld\n", (long) getpid());

  return 0;
}
