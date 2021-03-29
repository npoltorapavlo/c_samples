# usb-drive-listing

###### build

```shell script
$ sudo apt-get install -y libudev-dev

$ g++ -std=c++11 \
  -o usb-drive-listing \
  -I . -I ./src \
  usb-drive-listing.cpp \
  src/controller/*.cpp \
  src/sys/*.cpp \
  src/udev/*.cpp \
  -lpthread -ludev
```

###### run

```shell script
$ ./usb-drive-listing 
Press any key to exit...
Mon Mar 29 15:26:31 2021

 (0) /dev/sdb1 (sdb1,partition) mounted as /media/npoltorapavlo/7807-13C9
 (1) /dev/sdb2 (sdb2,partition) mounted as /media/npoltorapavlo/18dcd108-4baf-4067-b382-ce3bcf7f96b5
 (2) /dev/sdc (sdc,disk) mounted as /media/npoltorapavlo/7a79e328-8937-4019-9131-0b24d77043eb
 (3) /dev/sdb (sdb,disk) 

Mon Mar 29 15:26:35 2021

 (0) /dev/sdb1 (sdb1,partition) mounted as /media/npoltorapavlo/7807-13C9
 (1) /dev/sdc (sdc,disk) mounted as /media/npoltorapavlo/7a79e328-8937-4019-9131-0b24d77043eb
 (2) /dev/sdb (sdb,disk) 

Mon Mar 29 15:26:35 2021

 (0) /dev/sdc (sdc,disk) mounted as /media/npoltorapavlo/7a79e328-8937-4019-9131-0b24d77043eb
 (1) /dev/sdb (sdb,disk) 

Mon Mar 29 15:26:36 2021

 (0) /dev/sdc (sdc,disk) mounted as /media/npoltorapavlo/7a79e328-8937-4019-9131-0b24d77043eb

Mon Mar 29 15:26:46 2021


^C
```