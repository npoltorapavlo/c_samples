#include "systemclient.h"
#include "processinfo.h"

#include <thread>
#include <chrono>
#include <stdio.h>
#include <atomic>
#include <mutex>
#include <condition_variable>

using namespace std;

int numClientsNonRecreated = 2;
int numClientsRecreated = 2;

int main(int argc, char** argv) {

  if (argc > 1)
    numClientsNonRecreated = atoi(argv[1]);
  if (argc > 2)
    numClientsRecreated = atoi(argv[2]);

  atomic<bool> running(true);
  bool invokeProcessInfoNow = false;
  mutex mutex;
  condition_variable cond;

  vector<std::thread> workers;

  for (int i = 0; i < numClientsNonRecreated; i++) {
    workers.push_back(std::thread([&]() {
      SystemClient client;

      while (running) {
        if (!client.PrintInfo()) {
          std::unique_lock<std::mutex> lock(mutex);
          invokeProcessInfoNow = true;
          lock.unlock();
          cond.notify_one();
        }
      }
    }));
  }
  for (int i = 0; i < numClientsRecreated; i++) {
    workers.push_back(std::thread([&]() {
      while (running) {
        SystemClient client;
        if (!client.PrintInfo()) {
          std::unique_lock<std::mutex> lock(mutex);
          invokeProcessInfoNow = true;
          lock.unlock();
          cond.notify_one();
        }
      }
    }));
  }

  workers.push_back(std::thread([&]() {
    ProcessInfo client;

    while (running) {
      //client.PrintInfo(); // TODO why this crashes

      std::unique_lock<std::mutex> lock(mutex);
      cond.wait_for(lock, std::chrono::seconds(1), [&] { return !running || invokeProcessInfoNow; });
      invokeProcessInfoNow = false;
    }
  }));

  getchar();
  running = false;
  cond.notify_one();

  std::for_each(workers.begin(), workers.end(), [](std::thread &t) {
    t.join();
  });

  return 0;
}
