#ifndef C_SAMPLES_DEVICE_H
#define C_SAMPLES_DEVICE_H

#include <string>

class Device {
public:
  typedef enum {
    disk = 0,
    partition,
  } Devtype;

  Device() = delete;

  Device(const std::string &node, const std::string &sysname, Devtype devtype)
      : m_node(node), m_sysname(sysname), m_devtype(devtype) {}

  ~Device() = default;

  Device(const Device &copy) { operator=(copy); }

  Device &operator=(const Device &rhs) {
    m_node = rhs.m_node;
    m_sysname = rhs.m_sysname;
    m_devtype = rhs.m_devtype;
    return (*this);
  }

  inline bool operator==(const Device &RHS) const {
    return (m_node == RHS.m_node && m_sysname == RHS.m_sysname && m_devtype == RHS.m_devtype);
  }
  inline bool operator!=(const Device &RHS) const {
    return !(operator==(RHS));
  }
  inline bool operator<=(const Device &rhs) const {
    return (m_node <= rhs.m_node);
  }
  inline bool operator>=(const Device &rhs) const {
    return (m_node >= rhs.m_node);
  }
  inline bool operator<(const Device &rhs) const {
    return (m_node < rhs.m_node);
  }
  inline bool operator>(const Device &rhs) const {
    return (m_node > rhs.m_node);
  }

  std::string Node() { return m_node; }

  std::string Sysname() { return m_sysname; }

  Devtype GetDevtype() { return m_devtype; }

private:
  std::string m_node;
  std::string m_sysname;
  Devtype m_devtype;
};

#endif //C_SAMPLES_DEVICE_H
