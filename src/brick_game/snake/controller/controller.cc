#include "controller.h"

#include "../model/model.h"

void ControllerSnake(SignalType signal, Parameters *p_parameters) {
  s21::Model model{};
  model.SetSignalType(signal);
  model.SetParameters(p_parameters);
  model.SignalAction();
}