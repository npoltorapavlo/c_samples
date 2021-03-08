# thread-corrupt-stack

###### build

```shell script
$ git clean -fdx && cmake . && make
or
$ git clean -fdx && cmake . -DJOIN_THREAD_ON_EXIT=ON && make
```

###### run

```shell script
$ ulimit -c unlimited

$ ./thread-corrupt-stack 
~SharedLibraryImp
Unloaded library: sharedlibrary/libsharedlibrary.so
Segmentation fault (core dumped)

$ gdb thread-corrupt-stack core
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x00007f300687d600 in ?? ()
[Current thread is 1 (Thread 0x7f30062fe700 (LWP 20712))]
(gdb) thread apply all bt

Thread 2 (Thread 0x7f30062ff740 (LWP 20711)):
#0  0x00007f30065333bf in __GI___clock_nanosleep (clock_id=clock_id@entry=0, flags=flags@entry=0, req=0x7fffc7f050a0, rem=0x7fffc7f050a0) at ../sysdeps/unix/sysv/linux/clock_nanosleep.c:78
#1  0x00007f3006539047 in __GI___nanosleep (requested_time=<optimized out>, remaining=<optimized out>) at nanosleep.c:27
#2  0x000055c043e008ce in void std::this_thread::sleep_for<long, std::ratio<1l, 1l> >(std::chrono::duration<long, std::ratio<1l, 1l> > const&) ()
#3  0x000055c043e003d8 in main ()

Thread 1 (Thread 0x7f30062fe700 (LWP 20712)):
#0  0x00007f300687d600 in ?? ()
#1  0x00007f300684a609 in start_thread (arg=<optimized out>) at pthread_create.c:477
#2  0x00007f3006575293 in clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95
```

###### w/ JOIN_THREAD_ON_EXIT

```shell script
$ ./thread-corrupt-stack 
~SharedLibraryImp
threadRun done
Unloaded library: sharedlibrary/libsharedlibrary.so
```
