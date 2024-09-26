#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_BACKEND_BACKEND_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_BACKEND_BACKEND_H_

#include <string.h>

#include "../../common/block/block.h"
#include "../../common/board/board.h"
#include "../../common/cell/cell.h"
#include "../../common/collisions_checker/collisions_checker.h"
#include "../../common/game_status/game_status.h"
#include "../../common/parameters/parameters.h"
#include "../../common/player/player.h"
#include "../../common/records/records.h"
#include "../../common/time_handler/time_handler.h"

#define MAX_LEVEL_COUNT (10)

#ifdef __cplusplus
extern "C" {
#endif

static const long long kArrayOfTimeStep[11] = {1000, 875, 625, 550, 425, 350,
                                               325,  300, 250, 200, 150};

void BoardOverlayBlock(Player *p_player, Board *p_board);
void MovePredictPlayerDown(Player *p_player, Board *p_board);
void UpdatePredictPlayer(Player *p_player_dest, Player player_src,
                         Board *p_board);
long long int GetTimeStepMS(GameStatus *p_game_status);

#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_TETRIS_BACKEND_BACKEND_H_