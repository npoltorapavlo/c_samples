#include "unixsocket.h"

#include <errno.h>
#include <cstdio>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>

bool UnixSocket::Create() {
  bool result = false;

  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    printf("%s:%d [%s][%d] socket %d (%s)\n",
           __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
  } else {
    printf("%s:%d [%s][%d] created\n",
           __FILE__, __LINE__, __func__, fd);
    result = true;
  }

  return result;
}

bool UnixSocket::Listen(const struct sockaddr *addr, socklen_t addrlen, int backlog) {
  if (unlink(addr->sa_data) == -1) {
    printf("%s:%d [%s][%d] unlink %d (%s)\n",
           __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
  } else {
    printf("%s:%d [%s][%d] unlinked %s\n",
           __FILE__, __LINE__, __func__, fd, addr->sa_data);
  }

  return Socket::Listen(addr, addrlen, backlog);
}

bool UnixSocket::Connect(const char* path) {
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, path, sizeof(addr.sun_path));
  addr.sun_path[sizeof(addr.sun_path) - 1] = '\0';

  return Socket::Connect((struct sockaddr *)&addr, sizeof(addr));
}

bool UnixSocket::Listen(const char* path, int backlog) {
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, path, sizeof(addr.sun_path));
  addr.sun_path[sizeof(addr.sun_path) - 1] = '\0';

  return Listen((struct sockaddr *)&addr, sizeof(addr), backlog);
}
