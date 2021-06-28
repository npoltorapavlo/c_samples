#ifndef C_SAMPLES_UNIXSOCKET_H
#define C_SAMPLES_UNIXSOCKET_H

#include "socket.h"

class UnixSocket : public Socket {
public:
  virtual ~UnixSocket() = default;
  virtual bool Create() override;
  virtual bool Listen(const struct sockaddr *addr, socklen_t addrlen, int backlog) override;

public:
  virtual bool Connect(const char* path);
  virtual bool Listen(const char* path, int backlog);
};

#endif //C_SAMPLES_UNIXSOCKET_H
