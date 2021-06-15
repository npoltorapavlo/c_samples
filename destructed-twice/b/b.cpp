#include "b.h"

#include <lib.h>

#include <iostream>

void B::print() const {
  unsigned char buffer[128];
  get_token(sizeof(buffer), buffer);
  std::cout << buffer << std::endl;
}
