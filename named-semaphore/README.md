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
