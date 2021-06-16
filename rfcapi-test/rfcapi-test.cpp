#include "rfcutils.h"

#include "textgen.h"
#include "rfcapi.h" // for MAX_PARAM_LEN

using namespace std;

int main(int argc, char** argv) {
  
  string caller = ((argc > 1) ? argv[1] : "Warehouse");
  string name = ((argc > 2) ? argv[2] : "Device.DeviceInfo.X_RDKCENTRAL-COM_RFC.CommonProperties.WarehouseHost.CName2");
  string value;
  string max = TextGen::generateRandomString(MAX_PARAM_LEN);
  string overflow = TextGen::generateRandomString(MAX_PARAM_LEN * 2);

  RFCUtils::getRFC(name, value, caller);
  RFCUtils::setRFC(name, max, caller);
  RFCUtils::getRFC(name, value, caller);
  RFCUtils::setRFC(name, overflow, caller);
  RFCUtils::getRFC(name, value, caller);

  return 0;
}
