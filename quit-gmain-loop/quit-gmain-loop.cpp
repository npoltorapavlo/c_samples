#include "dynloader.h"
#include "service.h"
#include "plugin.h"

#include <chrono>
#include <thread>

int main(int argc, char** argv) {

  {
    DynLoader myLib(
#ifdef __APPLE__
        "libplugin.dylib"
#else
        "libplugin.so"
#endif
    );

    myLib.open();

    IPlugin *plugin = ServiceAdmin::Instance().Instantiate<IPlugin>("Plugin");
    plugin->Init();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    delete plugin;
  }

  std::this_thread::sleep_for(std::chrono::seconds(5));

  return 0;
}
