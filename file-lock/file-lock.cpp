#include "critsection.h"

#include <unistd.h>
#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv) {
  int numForks = ((argc > 1) ? atoi(argv[1]) : 3);

  printf("starting pid %ld numForks=%d\n", (long) getpid(), numForks);

  for (int i = 0; i < numForks; i++) {
    pid_t pid = fork();
    if (pid == 0) {
      printf("forked child process pid %ld\n", (long) getpid());
      critSection();
      break;
    }
  }

  printf("ending pid %ld\n", (long) getpid());

  return 0;
}
