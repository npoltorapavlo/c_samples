#ifndef C_SAMPLES_OUTPUT_H
#define C_SAMPLES_OUTPUT_H

#include "controller/devicecontroller.h"

template<typename DEVICECONTROLLER>
class Output {
public:
  Output() : m_controller(std::bind(&Output::Update, this)) {}
  virtual ~Output() = default;

  virtual void Initialize() {
    m_controller.Load();
    Update();
    m_controller.Monitor();
  }

  virtual void DeInitialize() {
    m_controller.DeMonitor();
  }

  virtual void Update() = 0;

protected:
  DEVICECONTROLLER m_controller;
};

#endif //C_SAMPLES_OUTPUT_H
