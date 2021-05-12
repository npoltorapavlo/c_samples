# wpeframework-test

This sample uses WPEFramework (https://github.com/rdkcentral/Thunder) and builds for RDK. Arg1 - num of concurrent clients, arg2 - num of concurrent clients which recreate JSONRPC::LinkType. Defaults are 2.
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