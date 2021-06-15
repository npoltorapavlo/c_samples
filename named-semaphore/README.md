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
starting pid 33187 numForks=3, programRun=10, semWait=20, critSectionRun=5
forked child process pid 33188
entering crit section pid 33188
forked child process pid 33189
entering crit section pid 33189
forked child process pid 33190
entering crit section pid 33190
entered crit section pid 33188
leaving crit section pid 33188
entered crit section pid 33189
ending pid 33187
leaving crit section pid 33189
entered crit section pid 33190
ending pid 33188
leaving crit section pid 33190
ending pid 33189
ending pid 33190
```
