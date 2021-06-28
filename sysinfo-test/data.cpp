#include "data.h"

Data::Data() : dataType(typeid(void*)) {
}

Data::Data(uint32_t data) : dataType(typeid(void*)) {
  setData(typeid(uint32_t), &data);
}

Data::Data(float data) : dataType(typeid(void*)) {
  setData(typeid(float), &data);
}

Data& Data::operator=(uint32_t value) {
  setData(typeid(uint32_t), &value);
  return *this;
}

Data& Data::operator=(float value) {
  setData(typeid(float), &value);
  return *this;
}

int32_t Data::toInteger32() const {
  if (dataType == typeid(uint32_t)) {
    return (int32_t)(unsignedInteger32Data);
  } else if (dataType == typeid(float)) {
    return (int32_t)(floatData);
  }
  return 0;
}

Data& Data::operator=(const Data& value) {
  std::type_index typeIndex = value.dataType;

  if (typeIndex == typeid(uint32_t)) {
    unsignedInteger32Data = value.unsignedInteger32Data;
    dataType = typeIndex;
  } else if (typeIndex == typeid(float)) {
    floatData = value.floatData;
    dataType = typeIndex;
  }
  return *this;
}

void Data::setData(std::type_index typeIndex, void* data) {
  if (typeIndex == typeid(uint32_t)) {
    unsignedInteger32Data = *((uint32_t *) data);
    dataType = typeIndex;
  } else if (typeIndex == typeid(float)) {
    floatData = *((float *) data);
    dataType = typeIndex;
  }
}
