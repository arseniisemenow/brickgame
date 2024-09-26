#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_ACTION_ACTION_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_ACTION_ACTION_H_

#include <iostream>
#include "../../common/fsm_types.h"
#include "../../common/parameters/parameters.h"

namespace s21 {
class Action {
 public:
  static void Start(Parameters *p_parameters);
  static void Spawn(Parameters *p_parameters);
  static void MovingUp(Parameters *p_parameters);
  static void MovingDown(Parameters *p_parameters);
  static void MovingLeft(Parameters *p_parameters);
  static void MovingRight(Parameters *p_parameters);
  static void Collide(Parameters *p_parameters);
  static void GameOver(Parameters *p_parameters);
  static void Exit(Parameters *p_parameters);
  static void Pause(Parameters *p_parameters);
};

}  // namespace s21

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_ACTION_ACTION_H_
