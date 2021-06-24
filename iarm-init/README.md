# iarm-init

This sample uses IARM and builds for RDK.

Arg1 - num concurrent threads to init IARM (default is 5).

###### build

```shell script
devtool add --autorev --src-subdir iarm-init iarm-init "https://github.com/npoltorapavlo/c_samples.git;branch=main"
devtool build iarm-init
devtool reset iarm-init
rm -rf workspace/sources/iarm-init
```

###### run

```shell script
root@pacexi5:~# /opt/iarm-init 
[706651838] init
[706651838] isConnected
IARM_Bus_IsConnected invalid state
[706651838] IARM_Bus_IsConnected: 2
[706651838] isConnected: 0
IARM_Init group name = com.comcast.rdk.iarm.bus member name = Thunder_Plugins
[868501336] init
[868501336] isConnected
[3883799080] init
[3883799080] isConnected
[573316671] init
[573316671] isConnected
[4027678456] init
[4027678456] isConnected
setting init done
IARM_Bus_IsConnected invalid state
[868501336] IARM_Bus_IsConnected: 2
[868501336] isConnected: 0
IARM_ASSERT Failed at [IARM_Bus_Init @ 105]
IARM_Bus_Init [Thunder_Plugins] Component Already registered with IARM; Invalid state
[868501336] IARM_Bus_Init: 2
Registering Thunder_Plugins
[868501336] IARM_Bus_Connect: 0
[868501336] isConnected
[868501336] IARM_Bus_IsConnected: 0
[868501336] isConnected: 1
[868501336] init: 1
[706651838] IARM_Bus_Init: 0
IARM_ASSERT Failed at [IARM_Bus_Connect @ 204]
[4027678456] IARM_Bus_IsConnected: 0
[4027678456] isConnected: 1
[4027678456] IARM already connected
[4027678456] init: 1
[3883799080] IARM_Bus_IsConnected: 0
[3883799080] isConnected: 1
[3883799080] IARM already connected
[3883799080] init: 1
[573316671] IARM_Bus_IsConnected: 0
[573316671] isConnected: 1
[573316671] IARM already connected
[573316671] init: 1
IARM_Bus_Connect invalid state
[706651838] IARM_Bus_Connect: 2
[706651838] isConnected
[706651838] IARM_Bus_IsConnected: 0
[706651838] isConnected: 1
[706651838] init: 1
```
