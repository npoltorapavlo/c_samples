#include "iarmutils.h"

#include "rdk/iarmbus/libIARM.h"
#include "libIBus.h"

#include <thread>
#include <functional>
#include <cstdio>

using namespace std;

bool Utils::IARM::init(const char* name) {
  uint32_t id = hash<thread::id>{}(this_thread::get_id());

  printf("[%lu] (re)checking if IARM is connected\n", id);

  IARM_Result_t res;
  int isRegistered = 0;
  res = IARM_Bus_IsConnected(name, &isRegistered);

  printf("[%lu] new=%d, res=%d\n", id, isRegistered, res);

  if (isRegistered > 0) {
    printf("[%lu] IARM already connected\n", id);
    return true;
  }

  res = IARM_Bus_Init(name);
  if (res == IARM_RESULT_SUCCESS) {
    res = IARM_Bus_Connect();
    if (res != IARM_RESULT_SUCCESS) {
      printf("[%lu] IARM_Bus_Connect failure: %d\n", id, res);
      res = IARM_Bus_Term();
      return false;
    }
  } else {
    printf("[%lu] IARM_Bus_Init failure: %d\n", id, res);
    return false;
  }

  printf("[%lu] IARM connected\n", id);

  return true;
}
