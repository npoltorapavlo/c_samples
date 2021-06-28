#include "websocket.h"

#include <errno.h>
#include <cstdio>
#include <string.h>
#include <netinet/in.h>

bool WebSocket::Create() {
  bool result = false;

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    printf("%s:%d [%s][%d] socket %d (%s)\n",
           __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
  } else {
    printf("%s:%d [%s][%d] created\n",
           __FILE__, __LINE__, __func__, fd);

    int opt = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1) {
      printf("%s:%d [%s][%d] setsockopt %d (%s)\n",
             __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
    }

    result = true;
  }

  return result;
}

bool WebSocket::Connect(uint16_t port) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  return Socket::Connect((struct sockaddr *)&addr, sizeof(addr));
}

bool WebSocket::Listen(uint16_t port, int backlog) {
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);

  return Socket::Listen((struct sockaddr *)&addr, sizeof(addr), backlog);
}
