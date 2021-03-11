#include "controller/usbdevicecontroller.h"

#include "stdoutput.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {

  cout << "Press any key to exit..." << '\n';

  StdOutput<UsbDeviceController> output;
  output.Initialize();

  cin.get();

  cout << "Closing..." << '\n';

  output.DeInitialize();

  return 0;
}
