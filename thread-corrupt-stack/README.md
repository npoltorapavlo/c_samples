# thread-corrupt-stack

###### build

```shell script
$ git clean -fdx && cmake . && make
or
$ git clean -fdx && cmake . -DJOIN_THREAD_ON_EXIT=ON && make
```

###### run

```shell script
$ ./thread-corrupt-stack 
Thread Run
Thread Run
Thread Run
Thread Run
Thread Run
libc++abi.dylib: terminating
Abort trap: 6

$ ./thread-corrupt-stack 
Thread Run
Thread Run
Thread Run
Thread Run
Thread Run
Thread Exit
Unloaded library: sharedlibrary/libsharedlibrary.dylib
```