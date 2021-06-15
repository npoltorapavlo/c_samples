# file-lock

Arg1 - num of child processes (default is 3).

###### build

```shell script
git clean -fdx && cmake . && make
```

###### run

```shell script
./file-lock 
starting pid 45696 numForks=3
forked child process pid 45697
entering crit section pid 45697
entered crit section pid 45697
ending pid 45696
forked child process pid 45698
entering crit section pid 45698
forked child process pid 45699
entering crit section pid 45699
leaving crit section pid 45697
ending pid 45697
entered crit section pid 45698
leaving crit section pid 45698
ending pid 45698
entered crit section pid 45699
leaving crit section pid 45699
ending pid 45699
```
