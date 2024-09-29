#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PLAYER_PLAYER_BOARD_PLAYER_BOARD_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PLAYER_PLAYER_BOARD_PLAYER_BOARD_H_

// #include "../../common/color_handler.h"
#include "../../block/block.h"
#include "../../cell/cell.h"

#define PLAYER_BOARD_SIZE (4)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  Cell **board_;
} PlayerBoard;

PlayerBoard * AllocPlayerBoard();
void FreePlayerBoard(PlayerBoard *p_player_board);

Cell* PlayerBoardGetCellXY(const PlayerBoard * player_board, const int x, const int y);

void PrintPlayerBoard(const PlayerBoard *p_player_board);

void InitPlayerBoard(PlayerBoard *p_player_board);
void CopyPlayerBoard(PlayerBoard *p_player_board_dest,
                     const PlayerBoard *p_player_board_src);

void SetPlayerBoardBlock(PlayerBoard *p_player_board, BlockType block_type,
                         Direction block_rotation);
#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PLAYER_PLAYER_BOARD_PLAYER_BOARD_H_
