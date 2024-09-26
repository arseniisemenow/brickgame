#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_MOVE_SNAKE_MOVE_SNAKE_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_MOVE_SNAKE_MOVE_SNAKE_H_

#include "../../common/parameters/parameters.h"

namespace s21 {
void MoveFruitToRandomPlace(Parameters *p_parameters);
void HandleCollideWithWall(Parameters *p_parameters);
void EatFruit(Parameters *p_parameters);
void HandleMoveHead(Parameters *p_parameters);
void MoveSnake(Parameters *p_parameters);
void HandleCollideWithItself(Parameters *p_parameters);
}  // namespace s21

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_MOVE_SNAKE_MOVE_SNAKE_H_
