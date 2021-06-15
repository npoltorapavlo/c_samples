# no-virtual

B derives from A. A::_1/_2 print A1/A2, _2 calls _1. B overrides _1, prints B1. _1, _2 are called from constructors. Test creates A, B on stack, B on heap (casted to A). For each calls _1, _2.

###### build

```shell script
$ git clean -fdx && cmake . && make
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
