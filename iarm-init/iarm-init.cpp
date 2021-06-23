#include "iarmutils.h"

#include <thread>
#include <list>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
  const int numThreads = ((argc > 1) ? atoi(argv[1]) : 5);
  const char* name = ((argc > 2) ? argv[2] : "test");

  list <thread> threads;
  for (int i = 0; i < numThreads; i++) {
    threads.emplace_back([&] {
      Utils::IARM::init(name);
    });
  }

  for (auto &i : threads) {
    i.join();
  }

  return 0;
}
