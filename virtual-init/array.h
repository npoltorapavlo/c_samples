#ifndef C_SAMPLES_ARRAY_H
#define C_SAMPLES_ARRAY_H

#include <vector>
#include <algorithm>

namespace Sample {

template <class T>
class Array {
public:
  using InitFn = void (*)(Array<T>* context, const T arr[], size_t n);

  // constructors
  Array(const T arr[], size_t n) : Array(arr, n, &Array::initInternal) {}
  Array(const T arr[], size_t n, InitFn initFn) {
    initFn(this, arr, n);
  }

  // destructor
  virtual ~Array() = default;

  // virtual functions
  virtual void init(const T arr[], size_t n) { initInternal(this, arr, n); }
  virtual const T& operator[](size_t i) { return m_vec[i]; }
  virtual size_t size() { return m_vec.size(); }
  virtual const T* data() { return m_vec.data(); }
  virtual void append(const T& item) { m_vec.emplace_back(item); }
  virtual void remove(const T& item) { m_vec.erase(std::remove(m_vec.begin(), m_vec.end(), item), m_vec.end()); }

private:
  // init
  static void initInternal(Array<T>* context, const T arr[], size_t n) {
    context->m_vec = std::vector(arr, arr + n);
  }

protected:
  // members
  std::vector<T> m_vec;
};

} // namespace Sample

#endif //C_SAMPLES_ARRAY_H
