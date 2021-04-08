# read-write-lock

Multiple threads read / write. Build with different locks to see the difference.

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

$ ./read-write-lock # READ_WRITE_LOCK
6333726 reads, 8566965 writes. Time: 229691 1133426

$ ./read-write-lock # ADVANCED_LOCK
2041191 reads, 11282798 writes. Time: 247971 920559
```
