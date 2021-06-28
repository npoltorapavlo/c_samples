#include "echosocket.h"
#include "websocket.h"
#include "unixsocket.h"

#include <thread>
#include <list>

using namespace std;

int main(int argc, char** argv) {
  // 1. web socket
  {
    const int port = 8099;
    const int backlog = 2;
    const int bufSize = 10;
    list<thread> threads;
    EchoSocket<WebSocket> server;
    EchoSocket<WebSocket> client1;
    EchoSocket<WebSocket> client2;
    EchoSocket<WebSocket> client3;
    server.Create();
    client1.Create();
    client2.Create();
    client3.Create();
    threads.emplace_back([&]() { server.Listen(port, backlog); });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    client1.Connect(port);
    client2.Connect(port);
    client3.Connect(port);
    threads.emplace_back([&]() { client1.Receive(bufSize); });
    threads.emplace_back([&]() { client2.Receive(bufSize); });
    threads.emplace_back([&]() { client3.Receive(bufSize); });
    client1.Write("test1", 5);
    client2.Write("test2", 5);
    client3.Write("test3", 5);
    threads.emplace_back([&]() {
      std::this_thread::sleep_for(std::chrono::seconds(2));
      server.Close();
    });
    for (auto &i : threads) {
      i.join();
    }
  }

  // 2. unix socket
  {

  }

  return 0;
}
