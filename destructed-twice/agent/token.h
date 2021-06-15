#pragma once

namespace utility {

  namespace agent {

    class token {
    public:
      token(const char* s);
      ~token();
      token(const token&) = delete;
      void operator=(const token&) = delete;
      const char* get() const;
      void copyTo(unsigned short maxLength, unsigned char buffer[]) const;
    private:
      char* m_p;
    };

  } // namespace agent

} // namespace utility
