#ifndef C_SAMPLES_UNIXSOCKET_H
#define C_SAMPLES_UNIXSOCKET_H

#include "socket.h"

class UnixSocket : public Socket {
public:
  UnixSocket() : Socket() {}
  UnixSocket(int new_fd) : Socket(new_fd) {}
  UnixSocket(const UnixSocket&) = delete;
  UnixSocket& operator=(UnixSocket const&) = delete;
  virtual ~UnixSocket() = default;

public:
  virtual bool Create() override;
  virtual bool Listen(const struct sockaddr *addr, socklen_t addrlen, int backlog) override;

public:
  virtual bool Connect(const char* path);
  virtual bool Listen(const char* path, int backlog);
};

#endif //C_SAMPLES_UNIXSOCKET_H
