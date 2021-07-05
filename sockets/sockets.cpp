#include "echosocket.h"
#include "websocket.h"
#include "unixsocket.h"

#include <thread>
#include <list>

using namespace std;

namespace {
  const int socketPort = 8099;
  const char* socketFile = "/tmp/test123";
  const int backlog = 5;
  const int bufSize = 10;
  const char* testData = "test";

  template <class SOCKET, class ADDR_ARG>
  void test(ADDR_ARG arg1, int numClients, int testTimeMs) {
    list<thread> threads;
    list<SOCKET> sockets(numClients + 1);

    // 1. Create N sockets
    for_each(sockets.begin(), sockets.end(), []( SOCKET& it) { it.Create(); });

    // 2. Socket1 listens, thread accepts connections
    sockets.front().Listen(arg1, backlog);
    threads.emplace_back([&]() { sockets.front().Accept(); });

    // 3. Socket2..N connect and write a message, thread receives data
    for_each(std::next(sockets.begin()), sockets.end(), [&](SOCKET& it) {
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
  int numClients = ((argc > 1) ? atoi(argv[1]) : 1);
  int testTimeMs = ((argc > 2) ? atoi(argv[2]) : 2000);

//  test<EchoSocket<WebSocket>>(socketPort, numClients, testTimeMs);
  test<EchoSocket<UnixSocket>>(socketFile, numClients, testTimeMs);
  return 0;
}
