# destructed-twice

```shell script
$ git clean -fdx && cmake . && make
```

```
$ ./app/app
foo
foo
~token0x7f4bf4fbb0b0
~token0x7f4bf4fbb0b0
free(): double free detected in tcache 2
Aborted (core dumped)
```

```
(gdb) b ~token
Breakpoint 1 at 0x7ffff7bd13ec (2 locations)
(gdb) i b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   <MULTIPLE>         
1.1                         y   0x00007ffff7bd13ec <utility::agent::token::~token()>
1.2                         y   0x00007ffff7fc34e6 <utility::agent::token::~token()>
(gdb) 

cat /proc/109646/maps
7ffff7bd1000-7ffff7bd2000 r-xp 00001000 08:02 12063983  .../lib/liblib.so
7ffff7fc3000-7ffff7fc4000 r-xp 00001000 08:02 12063990  .../a/liba.so

readelf -d ./app/app
0x0000000000000001 (NEEDED)             Shared library: [liba.so]
0x0000000000000001 (NEEDED)             Shared library: [libb.so]

readelf -d ./b/libb.so
0x0000000000000001 (NEEDED)             Shared library: [liblib.so]
```