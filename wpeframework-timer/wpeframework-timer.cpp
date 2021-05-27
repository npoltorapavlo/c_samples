#include "thunderclient.h"

#include <thread>
#include <chrono>
#include <stdlib.h>

int main(int argc, char** argv) {
  int clientRunMs = ((argc > 1) ? atoi(argv[1]) : 5500);

  ThunderClient* client = new ThunderClient;
  client->Init();

  std::this_thread::sleep_for(std::chrono::milliseconds(clientRunMs));

  client->DeInit();

  delete client;

  return 0;
}
