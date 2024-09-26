#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_BOARD_BOARD_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_BOARD_BOARD_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "../cell/cell.h"
// #include "../common/defines.h"

#define BOARD_HEIGHT (20)
#define BOARD_WIDTH (10)

typedef enum {
  kBoardSideUp = 0,
  kBoardSideDown = 1,
  kBoardSideLeft = 2,
  kBoardSideRight = 3,
} BoardSide;

typedef struct {
  int height_;
  int width_;
  Cell cells_[BOARD_HEIGHT][BOARD_WIDTH];
} Board;

void InitBoard(Board *p_board);
int HandleBoardCompleteLines(Board *p_board);
void RemoveBoardLine(Board *p_board, int line_index);
void ApplyPhysics(Board *p_board);
void ShiftBoardDown(Board *p_board, int empty_row_index);
void CopyBoardLine(Board *p_board, int index_dest, int index_src);
bool CheckBoardCompleteLine(Board *p_board, int row_index);

#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_BOARD_BOARD_H_
