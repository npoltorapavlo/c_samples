#include "lib.h"

#include <agent.h>

extern "C" {

void get_token(unsigned short maxLength, unsigned char buffer[]) {
  __get_token(maxLength, buffer);
}

} // extern "C"
