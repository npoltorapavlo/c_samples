#ifndef C_SAMPLES_WEBSOCKET_H
#define C_SAMPLES_WEBSOCKET_H

#include "socket.h"

#include <stdint.h>

class WebSocket : public Socket {
public:
  WebSocket() : Socket() {}
  WebSocket(int new_fd) : Socket(new_fd) {}
  WebSocket(const WebSocket&) = delete;
  WebSocket& operator=(WebSocket const&) = delete;
  virtual ~WebSocket() = default;

public:
  virtual bool Create() override;

public:
  virtual bool Connect(uint16_t port);
  virtual bool Listen(uint16_t port, int backlog);
};

#endif //C_SAMPLES_WEBSOCKET_H
