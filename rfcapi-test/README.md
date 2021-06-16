# rfcapi-test

This sample uses RFC and builds for RDK.

###### build

```shell script
devtool add --autorev --src-subdir rfcapi-test rfcapi-test "https://github.com/npoltorapavlo/c_samples.git;branch=main"
echo -e \
  'CXXFLAGS += " -I${STAGING_DIR_TARGET}${includedir}/wdmp-c/ "\n' \
  'CXXFLAGS += " -I${STAGING_DIR_TARGET}${includedir}/trower-base64/ "\n' \
  >> workspace/recipes/rfcapi-test/rfcapi-test_git.bb
devtool build rfcapi-test
devtool reset rfcapi-test
rm -rf workspace/sources/rfcapi-test
```

###### run

```shell script
root@pacexi5:~# /opt/rfcapi-test "Warehouse" "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.WarehouseHost.CName2"
getRFC name = Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.WarehouseHost.CName2, caller = Warehouse
getRFC name = Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.WarehouseHost.CName2, type = 0, value = cable.comcast.com
setRFC name = Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.WarehouseHost.CName2, type = 0, value = NWLRBB....., caller = Warehouse
getRFC name = Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.WarehouseHost.CName2, caller = Warehouse
getRFC name = Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.WarehouseHost.CName2, type = 0, value = NWLRBB.....
setRFC name = Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.WarehouseHost.CName2, type = 0, value = ZQSJWATYCBMJAWW....., caller = Warehouse
getRFC name = Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.WarehouseHost.CName2, caller = Warehouse
Segmentation fault (core dumped)
```
