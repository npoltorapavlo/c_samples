# wpeframework-test

This sample uses WPEFramework (https://github.com/rdkcentral/Thunder) and builds for RDK.

###### build

```shell script
devtool add --autorev --src-subdir wpeframework-errcode wpeframework-errcode "https://github.com/npoltorapavlo/c_samples.git;branch=wpeframework-errcode"
devtool build wpeframework-errcode
devtool reset wpeframework-errcode
rm -rf workspace/sources/wpeframework-errcode
```

###### run

```shell script
root@pacexi5:~# /opt/wpeframework-errcode true true
sToken, tokenStatus=103, token=eyJhbG....
[JSONRPCLink.h:163](Send)<10637><1>: Message: {"jsonrpc":"2.0","id":1,"method":"activate","params":{"callsign":"org.rdk.System.1"}} send
[JSONRPCLink.h:152](Received)<10637><1>: Message: {"jsonrpc":"2.0","id":1,"result":null} received
System activation succeeded
[JSONRPCLink.h:163](Send)<10637><1>: Message: {"jsonrpc":"2.0","id":2,"method":"org.rdk.System.1.getPowerStateBeforeReboot","params":{}} send
[JSONRPCLink.h:152](Received)<10637><1>: Message: {"jsonrpc":"2.0","id":2,"result":{"state":"","success":true}} received
getPowerStateBeforeReboot succeeded

root@pacexi5:~# systemctl restart wpeframework 
root@pacexi5:~# /opt/wpeframework-errcode true false
sToken, tokenStatus=103, token=eyJhbG....
[JSONRPCLink.h:163](Send)<16665><1>: Message: {"jsonrpc":"2.0","id":1,"method":"org.rdk.System.1.getPowerStateBeforeReboot","params":{}} send
[JSONRPCLink.h:152](Received)<16665><1>: Message: {"jsonrpc":"2.0","id":1,"error":{"code":-32603,"message":"Service is not active"}} received
getPowerStateBeforeReboot failed, errCode: 4294934693, result: '{}'

root@pacexi5:~# systemctl restart wpeframework
root@pacexi5:~# /opt/wpeframework-errcode           
[JSONRPCLink.h:163](Send)<22563><1>: Message: {"jsonrpc":"2.0","id":1,"method":"org.rdk.System.1.getPowerStateBeforeReboot","params":{}} send
getPowerStateBeforeReboot failed, errCode: 3, result: '{}'
```
