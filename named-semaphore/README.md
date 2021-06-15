# named-semaphore

Arg1 - num of child processes (default is 3).

###### build

```shell script
git clean -fdx && cmake . && make
```

###### run

```shell script
./named-semaphore 
starting pid 46649 numForks=3
forked child process pid 46650
entering crit section pid 46650
ending pid 46649
forked child process pid 46651
entering crit section pid 46651
entered crit section pid 46650
forked child process pid 46652
entering crit section pid 46652
leaving crit section pid 46650
entered crit section pid 46651
ending pid 46650
leaving crit section pid 46651
ending pid 46651
entered crit section pid 46652
leaving crit section pid 46652
ending pid 46652
```

If process crashes, semaphore state remains. App which waits for semaphore will be waiting indefinitely:

```shell script
hexdump /dev/shm/sem.critSection
0000000 0001 0000 0000 0000 0080 0000 0000 0000
0000010 0000 0000 0000 0000 0000 0000 0000 0000
0000020
hexdump locked
0000000 0000 0000 0000 0000 0080 0000 0000 0000
0000010 0000 0000 0000 0000 0000 0000 0000 0000
0000020
cp locked /dev/shm/sem.critSection
./named-semaphore 
starting pid 46599 numForks=3
forked child process pid 46600
entering crit section pid 46600
forked child process pid 46601
ending pid 46599
entering crit section pid 46601
forked child process pid 46602
entering crit section pid 46602
binarysemaphore.cpp:43 [Wait] sem_timedwait 110
```
