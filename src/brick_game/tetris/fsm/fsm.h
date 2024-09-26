#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_FSM_FSM_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_FSM_FSM_H_

#include "../../../gui/cli/frontend.h"
#include "../../common/collisions_checker/collisions_checker.h"
#include "../../common/common/defines.h"
#include "../../common/fsm_types.h"
#include "../backend/backend.h"
#include "callback.h"

#define KEY_DOWN 0402  /* down-arrow key */
#define KEY_UP 0403    /* up-arrow key */
#define KEY_LEFT 0404  /* left-arrow key */
#define KEY_RIGHT 0405 /* right-arrow key */
#define DELETE (127)
#define ESCAPE (27)
#define ENTER_KEY (10)
#define PAUSE_KEY ('p')

#ifdef __cplusplus
extern "C" {
#endif

SignalType GetSignal(int user_input, bool hold, bool *p_key_held);
void SignalAction(SignalType signal, Parameters *p_parameters);

void ActionSpawn(Parameters *p_parameters);

void ActionMoveUp(Parameters *p_parameters);

void ActionMoveDown(Parameters *p_parameters);

void ActionMoveRight(Parameters *p_parameters);

void ActionMoveLeft(Parameters *p_parameters);

void ActionCollide(Parameters *p_parameters);

void ActionGameOver(Parameters *p_parameters);

void ActionExitState(Parameters *p_parameters);

void ActionPause(Parameters *p_parameters);

bool CheckCollisions(Parameters *p_parameters);
#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_FSM_FSM_H_