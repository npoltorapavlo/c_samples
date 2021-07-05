# jsonrpc-test

This sample uses [JSONRPC::LinkType](https://github.com/rdkcentral/Thunder) and builds for RDK.

##### args

1. use token (default is "false").
2. activate plugin (default is "false").
3. plugin (default is "org.rdk.System.1").
4. method (default is "getPowerStateBeforeReboot").

##### build

```shell script
devtool add --autorev --src-subdir jsonrpc-test jsonrpc-test "https://github.com/npoltorapavlo/c_samples.git;branch=main"
devtool build jsonrpc-test
devtool reset jsonrpc-test
rm -rf workspace/sources/jsonrpc-test
```

##### run

```shell script
root@pacexi5:~# /opt/jsonrpc-test true true 
sToken, tokenStatus=103, token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.aHR0cDovL2xvY2FsaG9zdA.nGd09UHuj-R517QWWvvAmdoCHlg0NyN0290ccwttqjc
activate succeeded
method succeeded

root@pacexi5:~# systemctl restart wpeframework 
root@pacexi5:~# /opt/jsonrpc-test true false
sToken, tokenStatus=103, token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.aHR0cDovL2xvY2FsaG9zdA.nGd09UHuj-R517QWWvvAmdoCHlg0NyN0290ccwttqjc
method failed, errCode: 4294934693 (-32603), result: '{}

root@pacexi5:~# systemctl restart wpeframework
root@pacexi5:~# /opt/jsonrpc-test 
method failed, errCode: 3 (3), result: '{}'

root@pacexi5:~# systemctl stop netsrvmgr
root@pacexi5:~# systemctl restart wpeframework
root@pacexi5:~# /opt/jsonrpc-test true true "org.rdk.Network.1" ""
sToken, tokenStatus=103, token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.aHR0cDovL2xvY2FsaG9zdA.nGd09UHuj-R517QWWvvAmdoCHlg0NyN0290ccwttqjc
activate succeeded
```
