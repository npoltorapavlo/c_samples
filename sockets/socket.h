#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

class Socket {
public:
  Socket();
  Socket(int new_fd);
  Socket(const Socket&) = delete;
  Socket& operator=(Socket const&) = delete;
  virtual ~Socket();

public:
  virtual bool Create();
  virtual bool Connect(const struct sockaddr *addr, socklen_t addrlen);
  virtual bool Listen(const struct sockaddr *addr, socklen_t addrlen, int backlog);
  virtual void Accept();
  virtual bool Receive(size_t bufSize);
  virtual bool Write(const void *buf, size_t len);
  virtual bool Close();

protected:
  virtual void onAccepted(int new_fd, const struct sockaddr *addr, socklen_t addrlen) {}
  virtual void onReceived(const void *buf, size_t len) {}

protected:
  int fd;
};

#endif //SOCKET_H
