#include "cell.h"

#include <stdlib.h>

#include "../common/colors.h"

Cell *AllocCell() {
  Cell *cell = (Cell *)calloc(sizeof(Cell), 1);
  return cell;
}
void FreeCell(Cell *p_cell) { free(p_cell); }

char CellGetColor(Cell *p_cell) { return p_cell->color_; }
int CellGetIsSet(Cell *p_cell) { return p_cell->is_set_; }
int CellGetX(Cell *p_cell) { return p_cell->x_; }
int CellGetY(Cell *p_cell) { return p_cell->y_; }

void InitCell(Cell *p_cell) {
  p_cell->is_set_ = false;
  p_cell->color_ = COLOR_BLACK;
  p_cell->x_ = 0;
  p_cell->y_ = 0;
}

void CopyCell(Cell *p_cell_dest, Cell cell_src) {
  p_cell_dest->color_ = cell_src.color_;
  p_cell_dest->is_set_ = cell_src.is_set_;
  p_cell_dest->x_ = cell_src.x_;
  p_cell_dest->y_ = cell_src.y_;
}
