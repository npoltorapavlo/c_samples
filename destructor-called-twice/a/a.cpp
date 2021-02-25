#include "a.h"

#include <agent.h>

#include <iostream>

void A::print() const {
  unsigned char buffer[128];
  __get_token(sizeof(buffer), buffer);
  std::cout << buffer << std::endl;
}
