#include "agent.h"

#include "token.h"

extern "C" {

utility::agent::token _token("foo");

void __get_token(unsigned short maxLength, unsigned char buffer[]) {
  _token.copyTo(maxLength, buffer);
}

} // extern "C"
