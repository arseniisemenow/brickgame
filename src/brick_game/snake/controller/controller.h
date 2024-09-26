#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_CONTROLLER_CONTROLLER_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_CONTROLLER_CONTROLLER_H_

#include "../../common/fsm_types.h"
#include "../../common/parameters/parameters.h"
#include "../../common/time_handler/time_handler.h"

extern "C" void ControllerSnake(SignalType signal, Parameters *p_parameters);

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_SNAKE_CONTROLLER_CONTROLLER_H_