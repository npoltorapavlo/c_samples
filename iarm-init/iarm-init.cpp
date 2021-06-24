#include "iarmutils.h"

#include <thread>
#include <list>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
  const int numThreads = ((argc > 1) ? atoi(argv[1]) : 5);

  list <thread> threads;
  for (int i = 0; i < numThreads; i++) {
    threads.emplace_back([&] {
      Utils::IARM::init();
    });
  }

  for (auto &i : threads) {
    i.join();
  }

  return 0;
}
