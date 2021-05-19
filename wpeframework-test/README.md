# wpeframework-test

This sample uses WPEFramework (https://github.com/rdkcentral/Thunder) and builds for RDK.

Arg1 - num of concurrent clients (default is 2).
Arg2 - num of concurrent clients which recreate JSONRPC::LinkType (default is 2).
Arg3 - num of slow clients, each call takes ~5s (default is 0).

###### build

```shell script
devtool add --autorev --src-subdir wpeframework-test wpeframework-test "https://github.com/npoltorapavlo/c_samples.git;branch=main"
devtool build wpeframework-test
    #devtool edit-recipe wpeframework-test
    #vi workspace/sources/wpeframework-test/wpeframework-test/...
    #bitbake -C compile wpeframework-test
devtool reset wpeframework-test
rm -rf workspace/sources/wpeframework-test
```

###### run

```shell script
root@pacexi5:~# /opt/wpeframework-test > /opt/wpeframework-test.log 2>&1
root@pacexi5:~# /opt/wpeframework-test 10 10 > /opt/wpeframework-test.log 2>&1
```

###### out-of-threads problem

20 concurrent clients making ~5s calls + 1 client making normal calls. "pending" increased over 100, starting at some point all calls timed out, i.e. status=3, even though the responses were processed and received after the timeout.

```shell script
/opt/wpeframework-test 1 0 20 > /opt/wpeframework-test.log 2>&1

grep pending wpeframework-test.log |tail -n2
    [JSONRPCLink.h:152](Received)<15988><1>: Message: {"jsonrpc":"2.0","id":1842,"result":{"threads":[232,247,216,215,238,222,248,248,236],"pending":140,"occupation":8}} received
    [JSONRPCLink.h:152](Received)<15988><1>: Message: {"jsonrpc":"2.0","id":1865,"result":{"threads":[235,252,216,216,243,224,252,250,238],"pending":139,"occupation":8}} received
wc -l wpeframework-test.log
    6798 wpeframework-test.log
grep 'status=0' wpeframework-test.log |wc -l
    79
grep 'status=3' wpeframework-test.log |wc -l
    1862
grep -n 'status=0' wpeframework-test.log|tail -n1
    527:ActivatePlugin, callsign=org.rdk.Warehouse.1, status=0
    ^^^ <---- all next time out
grep -n 'status=3' wpeframework-test.log|tail -n1
    6738:InvokeJSONRPC, callsign=org.rdk.Warehouse.1, method=isClean, status=3
grep -n 'received' wpeframework-test.log|tail -n1
    6798:[JSONRPCLink.h:152](Received)<15988><1>: Message: {...} received
```

**Summary:** possible "status 3" reasons are: there is no token, WPEFramework crashed/stopped, method is slow (timeout), there are no available threads (timeout). Note, in case of timeout, a call is still processed and response is sent. Log indicates method processing if there is any logging for it. Also, since all calls from all clients are in queue, they all get "status 3".
