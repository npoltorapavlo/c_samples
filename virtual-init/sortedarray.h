#ifndef C_SAMPLES_SORTEDARRAY_H
#define C_SAMPLES_SORTEDARRAY_H

#include "array.h"

namespace Sample {

template <class T>
class SortedArray : public Array<T> {
public:
  // constructors
  SortedArray(const T arr[], size_t n) : Array<T>(arr, n, &SortedArray::initInternal) {}

  // destructor
  virtual ~SortedArray() = default;

  // virtual functions
  virtual void init(const T arr[], size_t n) override { initInternal(this, arr, n); }
  virtual void append(const T& item) override {
    this->m_vec.emplace(std::lower_bound(this->m_vec.begin(), this->m_vec.end(), item), item);
  }
  virtual void remove(const T& item) override {
    auto it = std::lower_bound(this->m_vec.begin(), this->m_vec.end(), item);
    while (it != this->m_vec.end() && *it == item) {
      it = this->m_vec.erase(it);
    }
  }

private:
  // init
  static void initInternal(Array<T>* context, const T arr[], size_t n) {
    SortedArray<T>* c = static_cast<SortedArray<T>*> (context);
    c->m_vec = std::vector(arr, arr + n);

    std::sort(std::begin(c->m_vec), std::end(c->m_vec));
  }
};

} // namespace Sample

#endif //C_SAMPLES_SORTEDARRAY_H
