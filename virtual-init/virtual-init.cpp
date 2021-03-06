#include "array.h"
#include "sortedarray.h"

#include <iostream>

#define SIZE(A) (sizeof(A) / sizeof(*A))

template <class T>
void printArray(const T arr[], size_t n) {
  std::copy(arr, arr + n, std::ostream_iterator<T>(std::cout, (std::is_same<T, char>::value) ? "" : " "));
  std::cout << std::endl;
}

template <class ARRAY, class T>
void testAppendAndRemove(const T arr1[], size_t n1, const T arr2[], size_t n2, const T arr3[], size_t n3) {
  std::unique_ptr<ARRAY> a(new ARRAY(arr1, n1)); // init
  printArray<T>(a->data(), a->size());
  std::for_each(arr2, arr2 + n2, [&](T v) { a->append(v); }); // append
  printArray<T>(a->data(), a->size());
  std::for_each(arr3, arr3 + n3, [&](T v) { a->remove(v); }); // remove
  printArray<T>(a->data(), a->size());
}

int main(int argc, char** argv) {
  {
    const int arr1[] = {10, 14, 28, 11, 7, 16, 30, 50, 25, 18, 0};
    const int arr2[] = {0, 4, 29395, -26, 17};
    const int arr3[] = {0, 1, 25};
    testAppendAndRemove<Sample::Array<int>, int>(arr1, SIZE(arr1), arr2, SIZE(arr2), arr3, SIZE(arr3));
    testAppendAndRemove<Sample::SortedArray<int>, int>(arr1, SIZE(arr1), arr2, SIZE(arr2), arr3, SIZE(arr3));
  }
  {
    const char* arr1 = "This is a text.";
    const char* arr2 = " This is another text.";
    const char arr3[] = {' ', '.'};
    testAppendAndRemove<Sample::Array<char>, char>(arr1, strlen(arr1), arr2, strlen(arr2), arr3, SIZE(arr3));
    testAppendAndRemove<Sample::SortedArray<char>, char>(arr1, strlen(arr1), arr2, strlen(arr2), arr3, SIZE(arr3));
  }

  return 0;
}
