# sysinfo-test

Checks if free ram is below 100 mb.
Sysinfo returns "unsigned long" (mem_unit is 1 if no overflow), can overflow on 32 bit 4gb+ ram. 

###### build

```shell script
g++ -std=c++11 -g -o sysinfo-test *.cpp

for RDK:
devtool add --autorev --src-subdir sysinfo-test sysinfo-test "https://github.com/npoltorapavlo/c_samples.git;branch=main"
devtool build sysinfo-test
devtool reset sysinfo-test
rm -rf sysinfo-test
```

###### run

```shell script
$ uname -m 
x86_64
$ ./sysinfo-test 
sysutils.cpp:25 [ram] sysinfo: 3083496 16378588 0 (mem_unit=1)
sysinfo-test.cpp:17 [main] freeKb: 3083496 isBelowThreshold: no

root@pacexi5:~# uname -m 
armv7l
root@pacexi5:~# /opt/sysinfo-test 
sysutils.cpp:25 [ram] sysinfo: 26748 624020 0 (mem_unit=1)
sysutils.cpp:41 [checkRam] ram 26.000000 below 100.000000
sysinfo-test.cpp:17 [main] freeKb: 26748 isBelowThreshold: yes
root@pacexi5:~# grep MemTotal /proc/meminfo 
MemTotal:         624020 kB

root@platco-cad11:~# uname -m
armv7l
root@platco-cad11:~# grep MemTotal /proc/meminfo 
MemTotal:        2830028 kB
```
