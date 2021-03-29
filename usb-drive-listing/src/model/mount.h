#ifndef C_SAMPLES_MOUNT_H
#define C_SAMPLES_MOUNT_H

#include <string>

class Mount {
public:
  Mount() = delete;
  Mount(const std::string& node, const std::string& path) : m_Node(node), m_Path(path) {}
  ~Mount() = default;

  Mount(const Mount& copy) { operator=(copy); }
  Mount& operator=(const Mount& rhs) {
    m_Node = rhs.m_Node;
    m_Path = rhs.m_Path;
    return (*this);
  }

  inline bool operator==(const Mount& RHS) const {
    return (m_Node == RHS.m_Node && m_Path == RHS.m_Path);
  }
  inline bool operator!=(const Mount& RHS) const {
    return !(operator==(RHS));
  }
  inline bool operator<=(const Mount& rhs) const {
    return (m_Node <= rhs.m_Node);
  }
  inline bool operator>=(const Mount& rhs) const {
    return (m_Node >= rhs.m_Node);
  }
  inline bool operator<(const Mount& rhs) const {
    return (m_Node < rhs.m_Node);
  }
  inline bool operator>(const Mount& rhs) const {
    return (m_Node > rhs.m_Node);
  }

  std::string Node() { return m_Node; }
  std::string Path() { return m_Path; }

private:
  std::string m_Node;
  std::string m_Path;
};

#endif //C_SAMPLES_MOUNT_H
