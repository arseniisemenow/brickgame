#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_CELL_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_CELL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct {
  unsigned char color_;
  bool is_set_;
  int x_;
  int y_;
} Cell;

void InitCell(Cell *p_cell);
void CopyCell(Cell *p_cell_dest, Cell cell_src);

#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_CELL_H_
