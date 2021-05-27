# wpeframework-timer

This sample uses WPEFramework (https://github.com/rdkcentral/Thunder) and builds for RDK.

Thunder client is making calls on timer (5500 ms). There's a race condition between timer callback and client/timer destruction.
Arg1 - client lifetime, ms (default is 5500).

###### build

```shell script
devtool add --autorev --src-subdir wpeframework-timer wpeframework-timer "https://github.com/npoltorapavlo/c_samples.git;branch=main"
devtool build wpeframework-timer
devtool reset wpeframework-timer
rm -rf workspace/sources/wpeframework-timer
```

###### run

```shell script
root@platco-cad11:~# /opt/wpeframework-timer 
token status: 103
[JSONRPCLink.h:159](Send)<15142><1>: Message: {"jsonrpc":"2.0","id":1,"method":"status@org.rdk.HdmiCecSink"} send
Getting status for callSign org.rdk.HdmiCecSink, result: activated
Starting the timer
onTimer
onTimer acquired lock
[JSONRPCLink.h:159](Send)<15142><1>: Message: {"jsonrpc":"2.0","id":2,"method":"status@org.rdk.HdmiCecSink"} send
~ThunderClient
Getting status for callSign org.rdk.HdmiCecSink, result: activated
Attempting to subscribe for event: arcInitiationEvent
[JSONRPCLink.h:159](Send)<15142><1>: Message: {"jsonrpc":"2.0","id":3,"method":"org.rdk.HdmiCecSink.1.register","params":{ "event": "arcInitiationEvent", "id": "org.rdk.HdmiCecSink.1"}} send
Subscribed for arcInitiationEvent
Attempting to subscribe for event: arcTerminationEvent
[JSONRPCLink.h:159](Send)<15142><1>: Message: {"jsonrpc":"2.0","id":4,"method":"org.rdk.HdmiCecSink.1.register","params":{ "event": "arcTerminationEvent", "id": "org.rdk.HdmiCecSink.1"}} send
Subscribed for arcTerminationEvent
Attempting to subscribe for event: shortAudiodesciptorEvent
[JSONRPCLink.h:159](Send)<15142><1>: Message: {"jsonrpc":"2.0","id":5,"method":"org.rdk.HdmiCecSink.1.register","params":{ "event": "shortAudiodesciptorEvent", "id": "org.rdk.HdmiCecSink.1"}} send
Subscribed for shortAudiodesciptorEvent
Timer stopped.
Subscription completed.
onTimer unlocked
~ThunderClient acquired lock
```
