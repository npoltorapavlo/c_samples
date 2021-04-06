# non-virtual-inherit

B derives from A. A:: f1/f2 print A1/A2, f2 calls f1. B overrides f1, prints B1. f1, f2 are called from constructors. Test creates A, B on stack, B on heap (casted to A). For each calls f1, f2.

###### build

```shell script
$ git clean -fdx && cmake . && make

w/ virtual:

$ git clean -fdx && cmake -DBUILD_WITH_VIRTUAL=ON . && make
```

###### run

```shell script
Ar A A1 A2 -> A1 A1 A2 -> A1 ~A ~Ar 
Ar A A1 A2 -> A1 Br B B1 A2 -> A1 B1 A2 -> A1 ~B ~Br ~A ~Ar 
Ar A A1 A2 -> A1 Br B B1 A2 -> A1 A1 A2 -> A1 ~A ~Ar
              ^^               ^^ ^^       ^^ -------------
w/ virtual:

Ar A A1 A2 -> A1 A1 A2 -> A1 ~A ~Ar 
Ar A A1 A2 -> A1 Br B B1 A2 -> B1 B1 A2 -> B1 ~B ~Br ~A ~Ar 
Ar A A1 A2 -> A1 Br B B1 A2 -> B1 B1 A2 -> B1 ~B ~Br ~A ~Ar 
              ^^               ^^ ^^       ^^ -------------
```
