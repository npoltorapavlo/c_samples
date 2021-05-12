# read-write-lock

Multiple threads read/write. Build with different locks to see the difference.

###### build

```shell script
g++ -std=c++11 -o read-write-lock *.cpp -lpthread
g++ -std=c++11 -o read-write-lock *.cpp -lpthread -DREAD_WRITE_LOCK
g++ -std=c++11 -o read-write-lock *.cpp -lpthread -DADVANCED_LOCK
```

###### run

```shell script
$ ./read-write-lock
terminate called after throwing an instance of 'std::invalid_argument'
  what():  stol
Aborted (core dumped)

# READ_WRITE_LOCK
$ ./read-write-lock
reads, time=36590336 (microseconds), count=4686702
writes, time=36816518 (microseconds), count=4554025

# ADVANCED_LOCK
$ ./read-write-lock
reads, time=38165326 (microseconds), count=2536283
writes, time=35928511 (microseconds), count=5964843
```
