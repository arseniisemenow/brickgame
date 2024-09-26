#include "controller.h"

#include "../Model/Model.h"

void ControllerSnake(SignalType signal, Parameters *p_parameters) {
  s21::Model model{};
  model.SetSignalType(signal);
  model.SetParameters(p_parameters);
  model.SignalAction();
}