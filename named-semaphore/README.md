# named-semaphore

Arg1 - num of child processes forked (default is 3).
Arg2 - program run time in seconds (default is 10).
Arg3 - semaphore wait time in seconds (default is 5).
Arg4 - critical section run time in seconds (default is 1).

###### build

```shell script
git clean -fdx && cmake . && make
```

###### run

```shell script
./named-semaphore 3 10 20 5
starting pid 34504 numForks=3, programRun=10, semWait=20, critSectionRun=5
forked child process pid 34505
entering crit section pid 34505
forked child process pid 34506
entering crit section pid 34506
forked child process pid 34507
entering crit section pid 34507
entered crit section pid 34505
leaving crit section pid 34505
entered crit section pid 34506
ending pid 34504
leaving crit section pid 34506
entered crit section pid 34507
ending pid 34505
leaving crit section pid 34507
ending pid 34506
ending pid 34507
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
starting pid 35951 numForks=3, programRun=10, semWait=5, critSectionRun=1
forked child process pid 35952
entering crit section pid 35952
forked child process pid 35953
entering crit section pid 35953
forked child process pid 35954
entering crit section pid 35954
binarysemaphore.cpp:43 [Wait] sem_timedwait 110
```
