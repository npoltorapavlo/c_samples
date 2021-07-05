#ifndef C_SAMPLES_ECHOSOCKET_H
#define C_SAMPLES_ECHOSOCKET_H

#include "socket.h"

#include <list>

template <class SOCKETTYPE>
class EchoSocket : public SOCKETTYPE {
public:
  EchoSocket() : SOCKETTYPE(), bytesReceived(0), bytesSent(0) {}
  EchoSocket(int new_fd) : SOCKETTYPE(new_fd), bytesReceived(0), bytesSent(0) {}
  ~EchoSocket() {
    printf("%s:%d [%s][%d] %ld connections, recv %ld bytes, sent %ld bytes\n",
           __FILE__, __LINE__, __func__, this->fd, connections.size(), bytesReceived, bytesSent);
    connections.clear();
    for (auto &i : receiveThreads) {
      i.join();
    }
  }

  EchoSocket(const EchoSocket<SOCKETTYPE>&) = delete;
  EchoSocket& operator=(EchoSocket<SOCKETTYPE> const&) = delete;

  bool Write(const void *buf, size_t len) override {
    bool result = Socket::Write(buf, len);
    if (result) {
      bytesSent += len;
    }
    return result;
  }

protected:
  virtual void onAccepted(int new_fd, const struct sockaddr *, socklen_t) override {
    printf("%s:%d [%s][%d] echo socket creates new echo socket %d\n",
           __FILE__, __LINE__, __func__, this->fd, new_fd);

    auto* new_socket = new EchoSocket<SOCKETTYPE>(new_fd);
    connections.emplace_back(new_socket);
    receiveThreads.emplace_back([&]() { new_socket->Receive(10); });
  }

  virtual void onReceived(const void *buf, size_t len) override {
    bytesReceived += len;

    Write(buf, len);
  }

private:
  std::list<std::shared_ptr<EchoSocket<SOCKETTYPE>>> connections;
  std::list<std::thread> receiveThreads;
  size_t bytesReceived;
  size_t bytesSent;
};

#endif //C_SAMPLES_ECHOSOCKET_H
