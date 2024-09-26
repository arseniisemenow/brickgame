#include "board.h"

void InitBoard(Board *p_board) {
  p_board->width_ = BOARD_WIDTH;
  p_board->height_ = BOARD_HEIGHT;
  for (int i = 0; i < p_board->height_; ++i) {
    for (int j = 0; j < p_board->width_; ++j) {
      InitCell(&p_board->cells_[i][j]);
    }
  }
}

int HandleBoardCompleteLines(Board *p_board) {
  int complete_lines_count = 0;
  for (int row_index = p_board->height_; row_index >= 0; --row_index) {
    for (int row_index_2 = p_board->height_; row_index_2 >= 0; --row_index_2) {
      bool flag = CheckBoardCompleteLine(p_board, row_index);
      if (flag) {
        complete_lines_count++;
        RemoveBoardLine(p_board, row_index);
        ApplyPhysics(p_board);
      }
    }
  }
  return complete_lines_count;
}
void RemoveBoardLine(Board *p_board, int line_index) {
  for (int column_index = 0; column_index < BOARD_WIDTH; ++column_index) {
    InitCell(&p_board->cells_[line_index][column_index]);
  }
}

bool CheckBoardCompleteLine(Board *p_board, int row_index) {
  bool flag = true;
  for (int column_index = 0; column_index < BOARD_WIDTH; ++column_index) {
    if (!p_board->cells_[row_index][column_index].is_set_) {
      flag = false;
    }
  }
  return flag;
}

void ApplyPhysics(Board *p_board) {
  for (int row_index = p_board->height_ - 1; row_index >= 0; --row_index) {
    bool empty_line_flag = true;
    for (int column_index = 0;
         column_index < p_board->width_ && empty_line_flag; ++column_index) {
      if (p_board->cells_[row_index][column_index].is_set_) {
        empty_line_flag = false;
      }
    }
    if (empty_line_flag) {
      ShiftBoardDown(p_board, row_index);
    }
  }
}

void ShiftBoardDown(Board *p_board, int empty_row_index) {
  for (int row_index = empty_row_index; row_index > 1; --row_index) {
    CopyBoardLine(p_board, row_index, row_index - 1);
  }
}

void CopyBoardLine(Board *p_board, int index_dest, int index_src) {
  for (int i = 0; i < BOARD_WIDTH; ++i) {
    CopyCell(&p_board->cells_[index_dest][i], p_board->cells_[index_src][i]);
  }
}