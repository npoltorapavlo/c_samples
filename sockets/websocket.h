#ifndef C_SAMPLES_WEBSOCKET_H
#define C_SAMPLES_WEBSOCKET_H

#include "socket.h"

#include <stdint.h>

class WebSocket : public Socket {
public:
  virtual ~WebSocket() = default;
  virtual bool Create() override;

public:
  virtual bool Connect(uint16_t port);
  virtual bool Listen(uint16_t port, int backlog);
};

#endif //C_SAMPLES_WEBSOCKET_H
