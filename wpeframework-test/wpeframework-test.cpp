#include "systemclient.h"
#include "processinfo.h"
#include "sleepinterrupt.h"

#include <thread>
#include <stdio.h>
#include <atomic>

using namespace std;

int numClientsNonRecreated = 2;
int numClientsRecreated = 2;

int main(int argc, char** argv) {

  if (argc > 1)
    numClientsNonRecreated = atoi(argv[1]);
  if (argc > 2)
    numClientsRecreated = atoi(argv[2]);

  atomic<bool> running(true);
  SleepInterrupt sleep;

  vector<std::thread> workers;

  for (int i = 0; i < numClientsNonRecreated; i++) {
    workers.push_back(std::thread([&]() {
      SystemClient client;

      while (running) {
        if (!client.PrintInfo()) {
          sleep.interrupt();
        }
      }
    }));
  }
  for (int i = 0; i < numClientsRecreated; i++) {
    workers.push_back(std::thread([&]() {
      while (running) {
        SystemClient client;
        if (!client.PrintInfo()) {
          sleep.interrupt();
        }
      }
    }));
  }

  workers.push_back(std::thread([&]() {
    ProcessInfo client;

    while (running) {
      //client.PrintInfo(); // TODO why this crashes

      sleep.sleep_for(std::chrono::seconds(1));
    }
  }));

  getchar();
  running = false;
  sleep.interrupt();

  std::for_each(workers.begin(), workers.end(), [](std::thread &t) {
    t.join();
  });

  return 0;
}
