#include "base64.h"

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <cassert>
#include <cstring>

using namespace std;

mutex mtx;
atomic<int> reading(0);

char* ptr = nullptr;

atomic<long> timeWrite(0);
atomic<long> timeRead(0);
atomic<long> numReads(0);
atomic<long> numWrites(0);

void write() {

#ifdef READ_WRITE_LOCK
  lock_guard<mutex> lck(mtx);
#elif ADVANCED_LOCK
  lock_guard<mutex> lck(mtx);
  while (reading > 0);
#endif

  auto start = chrono::steady_clock::now();

  long randomNumber = (long)rand() * 100l;
  string encoded = Base64::encode(to_string(randomNumber));

  if (ptr && strlen(ptr) == encoded.size())
    strcpy(ptr, encoded.c_str());
  else {
    if (ptr)
      free(ptr);
    ptr = strdup(encoded.c_str());
    assert(ptr != nullptr);
  }

  auto end = chrono::steady_clock::now();
  timeWrite += chrono::duration_cast<chrono::microseconds>(end - start).count();
  numWrites++;
}

void read() {

#ifdef READ_WRITE_LOCK
  lock_guard<mutex> lck(mtx);
#elif ADVANCED_LOCK
  {
    lock_guard<mutex> lck(mtx);
    reading++;
  }
#endif

  auto start = chrono::steady_clock::now();

  if (ptr != nullptr) {
    long decodedNumber = (stol(Base64::decode(string(ptr))));

    assert((decodedNumber % 100l) == 0);
  }

  auto end = chrono::steady_clock::now();
  timeRead += chrono::duration_cast<chrono::microseconds>(end - start).count();
  numReads++;

#ifdef ADVANCED_LOCK
  reading--;
#endif
}

int main(int argc, char** argv) {
  srand(time(nullptr));

  atomic<bool> running(true);

  thread w1([&] { while(running) write(); });
  thread w2([&] { while(running) write(); });
  thread r1([&] { while(running) read(); });
  thread r2([&] { while(running) read(); });

  std::this_thread::sleep_for(std::chrono::seconds(20));

  running = false;

  w1.join();
  w2.join();
  r1.join();
  r2.join();

  printf("%ld reads, %ld writes. Time: %ld %ld\n", (long)numReads, (long)numWrites, (long)timeRead, (long)timeWrite);

  return 0;
}
