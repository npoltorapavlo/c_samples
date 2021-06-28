#include "socket.h"

#include <errno.h>
#include <cstdio>
#include <string.h>
#include <unistd.h>

Socket::Socket()
  : fd(-1) {
}

Socket::Socket(int new_fd)
  : fd(new_fd) {
}

Socket::~Socket() {
  printf("%s:%d [%s][%d]\n",
         __FILE__, __LINE__, __func__, fd);

  Close();
}

bool Socket::Create() {
  return false;
}

bool Socket::Connect(const struct sockaddr *addr, socklen_t addrlen) {
  bool result = false;

  if (connect(fd, addr, addrlen) == -1) {
    printf("%s:%d [%s][%d] connect %d (%s)\n",
           __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
  } else {
    printf("%s:%d [%s][%d] connected\n",
           __FILE__, __LINE__, __func__, fd);
    result = true;
  }

  return result;
}

bool Socket::Listen(const struct sockaddr *addr, socklen_t addrlen, int backlog) {
  bool result = false;

  if (bind(fd, addr, addrlen) == -1) {
    printf("%s:%d [%s][%d] bind %d (%s)\n",
           __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
  } else if (listen(fd, backlog) == -1) {
    printf("%s:%d [%s][%d] listen %d (%s)\n",
           __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
  } else {
    printf("%s:%d [%s][%d] listening\n",
           __FILE__, __LINE__, __func__, fd);

    do {
      struct sockaddr address;
      int addrlen;
      int new_fd = accept(fd, &address, (socklen_t *)&addrlen); // blocking
      if (new_fd == -1) {
        printf("%s:%d [%s][%d] accept %d (%s)\n",
               __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
        break;
      } else {
        printf("%s:%d [%s][%d] accepted new connection\n",
               __FILE__, __LINE__, __func__, fd);
        onAccepted(new_fd, &address, (socklen_t)addrlen);
      }
    } while (true);

    result = true;
  }

  return result;
}

bool Socket::Receive(size_t bufSize) {
  bool result = false;

  do {
    char buf[bufSize];
    ssize_t n = recv(fd, buf, bufSize, 0); // blocking
    if (n <= 0) {
      if (n < 0) {
        printf("%s:%d [%s][%d] recv %d (%s)\n",
               __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
      } else {
        printf("%s:%d [%s][%d] recv eof/zero-length datagram\n",
               __FILE__, __LINE__, __func__, fd);
        result = true;
      }
      break;
    } else {
      printf("%s:%d [%s][%d] recv %ld bytes\n",
             __FILE__, __LINE__, __func__, fd, n);
      onReceived(buf, n);
    }
  } while (true);

  return result;
}

bool Socket::Write(const void *buf, size_t len) {
  bool result = false;

  if (send(fd, buf, len, 0) == -1) {
    printf("%s:%d [%s][%d] send %d (%s)\n",
           __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
  } else {
    printf("%s:%d [%s][%d] sent %lu bytes\n",
           __FILE__, __LINE__, __func__, fd, len);
    result = true;
  }

  return result;
}

bool Socket::Close() {
  bool result = false;

  if (close(fd) == -1) {
    printf("%s:%d [%s][%d] close %d (%s)\n",
           __FILE__, __LINE__, __func__, fd, errno, strerror(errno));
  } else {
    printf("%s:%d [%s][%d] closed\n",
           __FILE__, __LINE__, __func__, fd);
    result = true;
  }

  return result;
}
