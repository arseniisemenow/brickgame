#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_MODEL_MODEL_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_MODEL_MODEL_H_

#include <functional>

#include "../../common/fsm_types.h"
#include "../../common/parameters/parameters.h"
#include "../action/action.h"

namespace s21 {
inline constexpr long long kArrayOfTimeStep[11] = {500, 450, 400, 350, 300, 250,
                                                   225, 200, 175, 150, 125};
inline constexpr int kMaxLevelNumber = 10;

const std::function<void(Parameters *)> kFsmTable[7][8] = {
    {nullptr, nullptr, nullptr, nullptr, nullptr, Action::Exit, Action::Spawn,
     nullptr},
    {Action::Spawn, Action::Spawn, Action::Spawn, Action::Spawn, Action::Spawn,
     Action::Spawn, Action::Spawn, Action::Spawn},
    {nullptr, Action::MovingUp, Action::MovingDown, Action::MovingLeft,
     Action::MovingRight, Action::Exit, nullptr, Action::Pause},
    {Action::Collide, Action::Collide, Action::Collide, Action::Collide,
     Action::Collide, Action::Collide, Action::Collide, Action::Collide},
    {Action::GameOver, Action::GameOver, Action::GameOver, Action::GameOver,
     Action::GameOver, Action::GameOver, Action::GameOver, Action::GameOver},
    {Action::Exit, Action::Exit, Action::Exit, Action::Exit, Action::Exit,
     Action::Exit, Action::Exit, Action::Exit},
    {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
     Action::Pause},
};

class Model {
 public:
  Model();
  void SignalAction();
  void SetSignalType(SignalType signal_type);
  void SetParameters(Parameters *p_parameters);
  State GetState();
  SignalType GetSignal();
  Parameters *GetParameters();

 private:
  SignalType signal_type_;
  Parameters *p_parameters_;

  static long long int GetTimeStepMS(GameStatus *p_game_status);
};
}  // namespace s21

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_MODEL_MODEL_H_