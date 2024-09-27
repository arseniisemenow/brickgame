#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COLLISIONS_CHECKER_COLLISIONS_CHECKER_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COLLISIONS_CHECKER_COLLISIONS_CHECKER_H_

#include "../board/board.h"
#include "../parameters/parameters.h"
#include "../player/player.h"

#ifdef __cplusplus
extern "C" {
#endif

bool PerformCollideCheckWithSide(const Board *p_board,
                                 const BoardSide board_side, const int x,
                                 const int y);
bool CheckCollideWithSide(const Player *p_player, const Board *p_board,
                          const BoardSide board_side);
bool CheckCollideWithUp(const Player *p_player, const Board *p_board);
bool CheckCollideWithDown(const Player *p_player, const Board *p_board);
bool CheckCollideWithLeft(const Player *p_player, const Board *p_board);
bool CheckCollideWithRight(const Player *p_player, const Board *p_board);
bool CheckCollide(const Player *p_player, const Board *p_board);

bool PerformFutureCollideCheckWithSide(const Board *p_board,
                                       const BoardSide board_side, const int x,
                                       const int y);
bool CheckFutureCollideWithSide(Player *p_player, Board *p_board,
                                BoardSide board_side);
bool CheckFutureCollideWithUp(const Player *p_player, const Board *p_board);
bool CheckFutureCollideWithDown(const Player *p_player, const Board *p_board);
bool CheckFutureCollideWithLeft(const Player *p_player, const Board *p_board);
bool CheckFutureCollideWithRight(const Player *p_player, const Board *p_board);

bool CheckCollideWithBlocks(const Player *p_player, const Board *p_board);

bool CheckFutureCollideWithBlocksLeft(Player *p_player, Board *p_board);
bool CheckFutureCollideWithBlocksRight(Player *p_player, Board *p_board);
#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COLLISIONS_CHECKER_COLLISIONS_CHECKER_H_
