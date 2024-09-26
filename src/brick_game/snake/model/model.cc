#include "Model.h"

#include <unistd.h>

#include <iostream>

#include "../../common/time_handler/time_handler.h"
#include "../move_snake/move_snake.h"

namespace s21 {

Model::Model() {}

void Model::SignalAction() {
  State current_state = GetState();
  SignalType current_signal = GetSignal();
  Parameters *p_parameters = GetParameters();

  std::function<void(Parameters *)> action =
      kFsmTable[current_state][current_signal];

  if (action) {
    action(p_parameters);
  }

  long long time_in_ms = GetTimeInMS();

  if (*p_parameters->t_state_ == kMoving) {
    long long time_step = GetTimeStepMS(p_parameters->s_game_status_);
    if (time_in_ms - *p_parameters->s_last_moved_time_ > time_step) {
      *p_parameters->s_last_moved_time_ = time_in_ms;
      MoveSnake(p_parameters);
    }
  }
}
void Model::SetParameters(Parameters *p_parameters) {
  p_parameters_ = p_parameters;
}
void Model::SetSignalType(SignalType signal_type) {
  signal_type_ = signal_type;
}
State Model::GetState() { return *p_parameters_->s_state_; }
SignalType Model::GetSignal() { return signal_type_; }
Parameters *Model::GetParameters() { return p_parameters_; }

long long int Model::GetTimeStepMS(GameStatus *p_game_status) {
  if (p_game_status->level_ > kMaxLevelNumber) {
    p_game_status->level_ = kMaxLevelNumber;
  }
  return kArrayOfTimeStep[p_game_status->level_];
}

}  // namespace s21