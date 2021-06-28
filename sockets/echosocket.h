#ifndef C_SAMPLES_ECHOSOCKET_H
#define C_SAMPLES_ECHOSOCKET_H

#include "socket.h"

#include <thread>

template <class SOCKETTYPE>
class EchoSocket : public SOCKETTYPE {
protected:
  virtual void onAccepted(int new_fd, const struct sockaddr *, socklen_t) override {
    printf("%s:%d [%s][%d] accepted new connection\n",
           __FILE__, __LINE__, __func__, this->fd);

    Socket new_socket(new_fd);
    new_socket.Receive(10);
  }

  virtual void onReceived(const void *buf, size_t len) override {
    printf("%s:%d [%s][%d] received %ld bytes\n",
           __FILE__, __LINE__, __func__, this->fd, len);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    Socket::Write(buf, len);
  }
};

#endif //C_SAMPLES_ECHOSOCKET_H
