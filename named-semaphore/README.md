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
starting pid 27176 numForks=3, programRun=10, semWait=20, critSectionRun=5
forked child process pid 27177
entering crit section pid 27177
forked child process pid 27178
entering crit section pid 27178
forked child process pid 27179
entering crit section pid 27179
entered crit section pid 27177
leaving crit section pid 27177
entered crit section pid 27178
ending pid 27176
leaving crit section pid 27178
entered crit section pid 27179
ending pid 27177
leaving crit section pid 27179
ending pid 27178
ending pid 27179
```
