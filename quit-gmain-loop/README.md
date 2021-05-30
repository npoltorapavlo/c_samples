# quit-gmain-loop

App loads a plugin via dlopen, waits 5s, then destroys and unloads it.
Plugin runs a GMainLoop and calls g_main_loop_quit in destructor, which doesn't stop the sources that have already been dispatched.
As a result, SEGV with unknown address.

###### build

```shell script
$ brew install glib # macos
$ git clean -fdx && cmake . && make
or
$ git clean -fdx && cmake . -DJOIN_THREAD_ON_EXIT=ON && make
```

###### run (w/o JOIN_THREAD_ON_EXIT)

```shell script
$ lldb ./quit-gmain-loop
(lldb) r
startUp
Init
pluginThreadInit
pluginThreadStart
adding a sec timer
pluginThreadWork
pluginThreadWork done
pluginThreadWork
pluginThreadWork done
work
work done
pluginThreadWork
pluginThreadWork done
work
~Plugin
pluginThreadStop
pluginThreadTerm
Unloaded library: libplugin.dylib
Process 34166 stopped
* thread #2, stop reason = EXC_BAD_ACCESS (code=1, address=0x10015480e)
    frame #0: 0x000000010015480e
error: memory read failed for 0x100154800
Target 0: (quit-gmain-loop) stopped.
(lldb) bt all
  thread #1, queue = 'com.apple.main-thread'
    frame #0: 0x00007fff205e0c22 libsystem_kernel.dylib`__semwait_signal + 10
    frame #1: 0x00007fff20560c2a libsystem_c.dylib`nanosleep + 196
    frame #2: 0x00007fff205b393a libc++.1.dylib`std::__1::this_thread::sleep_for(std::__1::chrono::duration<long long, std::__1::ratio<1l, 1000000000l> > const&) + 73
    frame #3: 0x000000010000321e quit-gmain-loop`void std::__1::this_thread::sleep_for<long long, std::__1::ratio<1l, 1l> >(std::__1::chrono::duration<long long, std::__1::ratio<1l, 1l> > const&) + 190
    frame #4: 0x00000001000030e2 quit-gmain-loop`main + 258
    frame #5: 0x00007fff2062ef3d libdyld.dylib`start + 1
    frame #6: 0x00007fff2062ef3d libdyld.dylib`start + 1
* thread #2, stop reason = EXC_BAD_ACCESS (code=1, address=0x10015480e)
  * frame #0: 0x000000010015480e
    frame #1: 0x0000700001e5ae80
    frame #2: 0x0000000100439854 libglib-2.0.0.dylib`g_timeout_dispatch + 20
    frame #3: 0x000000010043dc9c libglib-2.0.0.dylib`g_main_context_dispatch + 364
    frame #4: 0x000000010043e01d libglib-2.0.0.dylib`g_main_context_iterate + 525
    frame #5: 0x000000010043e34f libglib-2.0.0.dylib`g_main_loop_run + 239
(lldb) 
```
