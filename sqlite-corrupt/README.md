# sqlite-corrupt

###### build

```shell script
sudo apt-get update -y
sudo apt-get install -y libsqlite3-dev
git clean -fdx && cmake . && make
```

###### run

```shell script
./sqlite-corrupt 
Press any key to exit...
opening /tmp/sqlitetest
open /tmp/sqlitetest - success
create table - success
write '0' - success
write '1' - success
read '1' '12345' - success
read '0' '12345' - success
remove '1' - success
write '2' - success
write '3' - success
read '2' '12345' - success
read '3' '12345' - success
remove '2' - success
write '4' - success
write '5' - success
read '4' '12345' - success
read '0' '12345' - success
remove '0' - success
write '6' - success
write '7' - success
read '7' '12345' - success
read '6' '12345' - success
remove '7' - success
write '8' - success
write '9' - success
clean - success
sqlite error 8: attempt to write a readonly database
opening /tmp/sqlitetest
open /tmp/sqlitetest - success
create table - success
write '10' - success
write '11' - success
read '10' '12345' - success
read '11' '12345' - success
remove '11' - success
write '12' - success
write '13' - success
read '12' '12345' - success
read '10' '12345' - success
remove '10' - success
write '14' - success
write '15' - success
read '14' '12345' - success
read '14' '12345' - success
remove '15' - success
write '16' - success
write '17' - success
read '17' '12345' - success
read '14' '12345' - success
remove '14' - success
write '18' - success
write '19' - success
clean - success
sqlite error 8: attempt to write a readonly database
opening /tmp/sqlitetest
open /tmp/sqlitetest - success
create table - success
write '20' - success
write '21' - success
read '20' '12345' - success
read '20' '12345' - success
remove '20' - success
write '22' - success
write '23' - success
read '22' '12345' - success
read '22' '12345' - success
remove '22' - success
write '24' - success
write '25' - success
read '24' '12345' - success
read '24' '12345' - success
remove '24' - success
write '26' - success
write '27' - success
read '26' '12345' - success
read '26' '12345' - success
remove '27' - success
clean - success
sqlite error 8: attempt to write a readonly database
opening /tmp/sqlitetest
open /tmp/sqlitetest - success
create table - success
write '28' - success
write '29' - success
remove '29' - success
read '28' '12345' - success
read '28' '12345' - success
write '30' - success
write '31' - success
remove '30' - success
read '28' '12345' - success
read '28' '12345' - success
write '32' - success
write '33' - success
remove '33' - success
read '28' '12345' - success
read '28' '12345' - success
write '34' - success
write '35' - success
remove '34' - success
read '32' '12345' - success
read '32' '12345' - success
write '36' - success
write '37' - success
clean - success
sqlite error 8: attempt to write a readonly database
opening /tmp/sqlitetest
open /tmp/sqlitetest - success
create table - success
write '38' - success
write '39' - success
remove '39' - success
read '38' '12345' - success
read '38' '12345' - success
write '40' - success
write '41' - success
remove '40' - success
read '38' '12345' - success
read '38' '12345' - success
write '42' - success
write '43' - success
remove '42' - success
sqlite error 101: no more rows available
read '42' '' - failure
read '38' '12345' - success
write '44' - success
write '45' - success
remove '38' - success
sqlite error 101: no more rows available
read '38' '' - failure
read '45' '12345' - success
clean - success
sqlite error 8: attempt to write a readonly database
opening /tmp/sqlitetest
open /tmp/sqlitetest - success
create table - success
write '46' - success
write '47' - success
remove '46' - success
read '47' '12345' - success
sqlite error 101: no more rows available
read '46' '' - failure
write '48' - success
write '49' - success
remove '48' - success
read '49' '12345' - success
sqlite error 101: no more rows available
read '48' '' - failure
write '50' - success
write '51' - success
remove '51' - success
read '50' '12345' - success
sqlite error 101: no more rows available
read '51' '' - failure
write '52' - success
^C

```
