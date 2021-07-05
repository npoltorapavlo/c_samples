#ifndef C_SAMPLES_DATA_H
#define C_SAMPLES_DATA_H

#include <typeindex>
#include <stdint.h>

class Data {
public:
  Data();
  Data(uint32_t data);
  Data(float data);
  Data& operator=(uint32_t value);
  Data& operator=(float value);
  Data& operator=(const Data& value);
  int32_t toInteger32() const;

private:
  void setData(std::type_index typeIndex, void* data);

private:
  std::type_index dataType;
  uint32_t unsignedInteger32Data;
  float floatData;
};

#endif //C_SAMPLES_DATA_H
