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
```