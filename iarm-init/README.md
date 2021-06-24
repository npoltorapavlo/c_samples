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
[2526534237] (re)checking if IARM is connected
IARM_Bus_IsConnected invalid state
[2526534237] new=0, res=2
[1845321295] (re)checking if IARM is connected
IARM_Init group name = com.comcast.rdk.iarm.bus member name = test
[415783568] (re)checking if IARM is connected
[2651383302] (re)checking if IARM is connected
[1457405924] (re)checking if IARM is connected
setting init done
IARM_Bus_IsConnected invalid state
[1845321295] new=0, res=2
IARM_ASSERT Failed at [IARM_Bus_Init @ 105]
IARM_Bus_Init [test] Component Already registered with IARM; Invalid state
[1845321295] IARM_Bus_Init failure: 2
IARM_Bus_IsConnected invalid state
[415783568] new=0, res=2
IARM_ASSERT Failed at [IARM_Bus_Init @ 105]
IARM_Bus_Init [test] Component Already registered with IARM; Invalid state
[415783568] IARM_Bus_Init failure: 2
IARM_Bus_IsConnected invalid state
[2651383302] new=0, res=2
IARM_ASSERT Failed at [IARM_Bus_Init @ 105]
IARM_Bus_Init [test] Component Already registered with IARM; Invalid state
[2651383302] IARM_Bus_Init failure: 2
IARM_Bus_IsConnected invalid state
[1457405924] new=0, res=2
IARM_ASSERT Failed at [IARM_Bus_Init @ 105]
IARM_Bus_Init [test] Component Already registered with IARM; Invalid state
[1457405924] IARM_Bus_Init failure: 2
Registering test
[2526534237] IARM connected
```
