# sockets

Creates 1 listening socket and N connecting sockets.

Arg1 - port or location for the socket.
Arg2 - N (default is 1).
Arg3 - test time in ms (default is 2000).

###### build

```shell script
git clean -fdx && cmake . && make
```

###### run

1-1
```shell script
mykytas-mbp:sockets npoltorapavlo$ ./sockets "/tmp/test123"
unixsocket.cpp:17 [Create][3] created
unixsocket.cpp:17 [Create][4] created
unixsocket.cpp:30 [Listen][3] unlinked /tmp/test123
socket.cpp:55 [Listen][3] listening
socket.cpp:37 [Connect][4] connected
socket.cpp:73 [Accept][3] accepted new connection 5
echosocket.h:36 [onAccepted][3] echo socket creates new echo socket 5
echosocket.h:15 [~EchoSocket][3] 1 connections, recv 0 bytes, sent 0 bytes
echosocket.h:15 [~EchoSocket][5] 0 connections, recv 911540 bytes, sent 911540 bytes
socket.cpp:18 [~Socket][5] 0x7ff6ffd04080
socket.cpp:88 [Receive][5] recv 9 (Bad file descriptor)
socket.cpp:91 [Receive][4] recv eof/zero-length datagram
socket.cpp:124 [Close][5] closed
socket.cpp:18 [~Socket][3] 0x7ff6ffc05960
socket.cpp:69 [Accept][3] accept 53 (Software caused connection abort)
socket.cpp:124 [Close][3] closed
echosocket.h:15 [~EchoSocket][4] 0 connections, recv 911540 bytes, sent 911544 bytes
socket.cpp:18 [~Socket][4] 0x7ff6ffc059c0
socket.cpp:124 [Close][4] closed
```

1-N
```shell script
mykytas-mbp:sockets npoltorapavlo$ ./sockets "/tmp/test123" 5 30000
unixsocket.cpp:17 [Create][3] created
unixsocket.cpp:17 [Create][4] created
unixsocket.cpp:17 [Create][5] created
unixsocket.cpp:17 [Create][6] created
unixsocket.cpp:17 [Create][7] created
unixsocket.cpp:17 [Create][8] created
unixsocket.cpp:30 [Listen][3] unlinked /tmp/test123
socket.cpp:55 [Listen][3] listening
socket.cpp:37 [Connect][4] connected
socket.cpp:73 [Accept][3] accepted new connection 9
echosocket.h:36 [onAccepted][3] echo socket creates new echo socket 9
socket.cpp:37 [Connect][5] connected
socket.cpp:73 [Accept][3] accepted new connection 10
echosocket.h:36 [onAccepted][3] echo socket creates new echo socket 10
socket.cpp:37 [Connect][6] connected
socket.cpp:73 [Accept][3] accepted new connection 11
echosocket.h:36 [onAccepted][3] echo socket creates new echo socket 11
socket.cpp:37 [Connect][7] connected
socket.cpp:73 [Accept][3] accepted new connection 12
echosocket.h:36 [onAccepted][3] echo socket creates new echo socket 12
socket.cpp:37 [Connect][8] connected
socket.cpp:73 [Accept][3] accepted new connection 13
echosocket.h:36 [onAccepted][3] echo socket creates new echo socket 13
echosocket.h:15 [~EchoSocket][3] 5 connections, recv 0 bytes, sent 0 bytes
echosocket.h:15 [~EchoSocket][9] 0 connections, recv 5300300 bytes, sent 5300300 bytes
socket.cpp:18 [~Socket][9] 0x7ff295504080
socket.cpp:91 [Receive][4] recv eof/zero-length datagram
socket.cpp:88 [Receive][9] recv 9 (Bad file descriptor)
socket.cpp:124 [Close][9] closed
echosocket.h:15 [~EchoSocket][10] 0 connections, recv 5295040 bytes, sent 5295040 bytes
socket.cpp:18 [~Socket][10] 0x7ff295504180
socket.cpp:91 [Receive][5] recv eof/zero-length datagram
socket.cpp:124 [Close][10] closed
echosocket.h:15 [~EchoSocket][11] 0 connections, recv 5305260 bytes, sent 5305256 bytes
socket.cpp:18 [~Socket][11] 0x7ff295604080
socket.cpp:88 [Receive][10] recv 9 (Bad file descriptor)
socket.cpp:91 [Receive][6] recv eof/zero-length datagram
socket.cpp:124 [Close][11] closed
socket.cpp:88 [Receive][11] recv 9 (Bad file descriptor)
echosocket.h:15 [~EchoSocket][12] 0 connections, recv 5327448 bytes, sent 5327448 bytes
socket.cpp:18 [~Socket][12] 0x7ff295504280
socket.cpp:88 [Receive][12] recv 9 (Bad file descriptor)
socket.cpp:91 [Receive][7] recv eof/zero-length datagram
socket.cpp:124 [Close][12] closed
echosocket.h:15 [~EchoSocket][13] 0 connections, recv 5326156 bytes, sent 5326156 bytes
socket.cpp:18 [~Socket][13] 0x7ff295504380
socket.cpp:88 [Receive][13] recv 9 (Bad file descriptor)
socket.cpp:91 [Receive][8] recv eof/zero-length datagram
socket.cpp:124 [Close][13] closed
socket.cpp:18 [~Socket][3] 0x7ff295405960
socket.cpp:69 [Accept][3] accept 53 (Software caused connection abort)
socket.cpp:124 [Close][3] closed
echosocket.h:15 [~EchoSocket][4] 0 connections, recv 5300304 bytes, sent 5300308 bytes
socket.cpp:18 [~Socket][4] 0x7ff2954059c0
socket.cpp:124 [Close][4] closed
echosocket.h:15 [~EchoSocket][5] 0 connections, recv 5295040 bytes, sent 5295044 bytes
socket.cpp:18 [~Socket][5] 0x7ff295405a20
socket.cpp:124 [Close][5] closed
echosocket.h:15 [~EchoSocket][6] 0 connections, recv 5305260 bytes, sent 5305264 bytes
socket.cpp:18 [~Socket][6] 0x7ff295405a80
socket.cpp:124 [Close][6] closed
echosocket.h:15 [~EchoSocket][7] 0 connections, recv 5327456 bytes, sent 5327460 bytes
socket.cpp:18 [~Socket][7] 0x7ff295405ae0
socket.cpp:124 [Close][7] closed
echosocket.h:15 [~EchoSocket][8] 0 connections, recv 5326156 bytes, sent 5326160 bytes
socket.cpp:18 [~Socket][8] 0x7ff295405b40
socket.cpp:124 [Close][8] closed
```
