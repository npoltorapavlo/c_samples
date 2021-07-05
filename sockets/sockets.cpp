#include "echosocket.h"
#include "websocket.h"
#include "unixsocket.h"

#include <thread>
#include <list>

using namespace std;

namespace {
  const int backlog = 5;
  const int bufSize = 10;
  const char *testData = "test";

  template<class SOCKET, class ADDR_ARG>
  void test(ADDR_ARG arg1, int numClients, int testTimeMs) {
    list<thread> threads;
    list<SOCKET> sockets(numClients + 1);

    // 1. Create N sockets
    for_each(sockets.begin(), sockets.end(), [](SOCKET &it) { it.Create(); });

    // 2. Socket1 listens, thread accepts connections
    sockets.front().Listen(arg1, backlog);
    threads.emplace_back([&]() { sockets.front().Accept(); });

    // 3. Socket2..N connect and write a message, thread receives data
    for_each(std::next(sockets.begin()), sockets.end(), [&](SOCKET &it) {
      it.Connect(arg1);
      threads.emplace_back([&]() { it.Receive(bufSize); });
      it.Write(testData, strlen(testData));
    });

    // 4. Delete first socket
    threads.emplace_back([&]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(testTimeMs));
      sockets.pop_front();
    });

    // 5. Threads complete
    for (auto &i : threads) {
      i.join();
    }
  }
}

int main(int argc, char** argv) {
  const long int port = strtol(argv[1], nullptr, 10);
  const char* file = ((port == 0) ? argv[1] : nullptr);
  const int numClients = ((argc > 2) ? atoi(argv[2]) : 1);
  const int testTimeMs = ((argc > 3) ? atoi(argv[3]) : 2000);

  if (port == 0) {
    test<EchoSocket<UnixSocket>>(file, numClients, testTimeMs);
  } else {
    test<EchoSocket<WebSocket>>(port, numClients, testTimeMs);
  }

  return 0;
}
