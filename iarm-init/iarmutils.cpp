#include "iarmutils.h"

#include "rdk/iarmbus/libIARM.h"
#include "libIBus.h"

#include <thread>
#include <functional>
#include <cstdio>

using namespace std;

const char* Utils::IARM::NAME = "Thunder_Plugins";

bool Utils::IARM::isConnected() {
  uint32_t id = hash<thread::id>{}(this_thread::get_id());

  printf("[%lu] %s\n", id, __FUNCTION__);

  IARM_Result_t res;
  int isRegistered = 0;
  res = IARM_Bus_IsConnected(NAME, &isRegistered);
  printf("[%lu] IARM_Bus_IsConnected: %d\n", id, res);

  printf("[%lu] %s: %d\n", id, __FUNCTION__, isRegistered);

  return (isRegistered == 1);
}

bool Utils::IARM::init() {
  uint32_t id = hash<thread::id>{}(this_thread::get_id());

  printf("[%lu] %s\n", id, __FUNCTION__);

  IARM_Result_t res;
  bool result = false;

  if (isConnected()) {
    printf("[%lu] IARM already connected\n", id);
    result = true;
  } else {
    res = IARM_Bus_Init(NAME);
    printf("[%lu] IARM_Bus_Init: %d\n", id, res);
    if (res == IARM_RESULT_SUCCESS ||
      res == IARM_RESULT_INVALID_STATE /* already inited or connected */) {

      res = IARM_Bus_Connect();
      printf("[%lu] IARM_Bus_Connect: %d\n", id, res);
      if (res == IARM_RESULT_SUCCESS ||
        res == IARM_RESULT_INVALID_STATE /* already connected or not inited */) {

        result = isConnected();
      } else {
        printf("[%lu] IARM_Bus_Connect failure: %d\n", id, res);
      }
    } else {
      printf("[%lu] IARM_Bus_Init failure: %d\n", id, res);
    }
  }

  printf("[%lu] %s: %d\n", id, __FUNCTION__, result);

  return result;
}
