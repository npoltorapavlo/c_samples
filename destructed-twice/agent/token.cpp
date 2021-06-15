#include "token.h"

#include <iostream>
#include <cstring>

namespace utility {

namespace agent {

token::token(const char* s)
  : m_p(nullptr)
{
  if (s != nullptr) {
    m_p = new char[strlen(s) + 1];
    strcpy(m_p, s);
  }
}

token::~token() {
  std::cout << __FUNCTION__ << this << std::endl;

  if (m_p != nullptr) {
    delete[] m_p;
  }
}

const char* token::get() const {
  return m_p == nullptr ? "" : m_p;
}

void token::copyTo(unsigned short maxLength, unsigned char buffer[]) const {
  memcpy(buffer, get(), maxLength - 1);
  buffer[maxLength - 1] = '\0';
}

} // namespace agent
} // namespace utility