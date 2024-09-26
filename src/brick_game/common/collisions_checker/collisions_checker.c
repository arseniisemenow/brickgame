#include "collisions_checker.h"

bool CheckFutureCollideWithUp(Player *p_player, Board *p_board) {
  return CheckFutureCollideWithSide(p_player, p_board, kBoardSideUp);
}
bool CheckFutureCollideWithDown(Player *p_player, Board *p_board) {
  return CheckFutureCollideWithSide(p_player, p_board, kBoardSideDown);
}
bool CheckFutureCollideWithLeft(Player *p_player, Board *p_board) {
  return CheckFutureCollideWithSide(p_player, p_board, kBoardSideLeft);
}
bool CheckFutureCollideWithRight(Player *p_player, Board *p_board) {
  return CheckFutureCollideWithSide(p_player, p_board, kBoardSideRight);
}

bool CheckCollideWithUp(Player *p_player, Board *p_board) {
  return CheckCollideWithSide(p_player, p_board, kBoardSideUp);
}
bool CheckCollideWithDown(Player *p_player, Board *p_board) {
  return CheckCollideWithSide(p_player, p_board, kBoardSideDown);
}
bool CheckCollideWithLeft(Player *p_player, Board *p_board) {
  return CheckCollideWithSide(p_player, p_board, kBoardSideLeft);
}
bool CheckCollideWithRight(Player *p_player, Board *p_board) {
  return CheckCollideWithSide(p_player, p_board, kBoardSideRight);
}

bool CheckCollide(Player *p_player, Board *p_board) {
  bool flag = CheckCollideWithUp(p_player, p_board);
  flag |= CheckCollideWithDown(p_player, p_board);
  flag |= CheckCollideWithLeft(p_player, p_board);
  flag |= CheckCollideWithRight(p_player, p_board);
  flag |= CheckCollideWithBlocks(p_player, p_board);
  return flag;
}

bool CheckCollideWithSide(Player *p_player, Board *p_board,
                          BoardSide board_side) {
  PlayerBoard *p_player_board = &p_player->board_;
  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      if (p_player_board->board_[row_index][column_index].is_set_) {
        int cell_global_pos_x = p_player->x_ + column_index;
        int cell_global_pos_y = p_player->y_ + row_index;
        bool flag = PerformCollideCheckWithSide(
            p_board, board_side, cell_global_pos_x, cell_global_pos_y);
        if (flag) {
          return flag;
        }
      }
    }
  }

  return false;
}

bool CheckFutureCollideWithSide(Player *p_player, Board *p_board,
                                BoardSide board_side) {
  PlayerBoard *p_player_board = &p_player->board_;
  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      if (p_player_board->board_[row_index][column_index].is_set_) {
        int cell_global_pos_x = p_player->x_ + column_index;
        int cell_global_pos_y = p_player->y_ + row_index;
        bool flag = PerformFutureCollideCheckWithSide(
            p_board, board_side, cell_global_pos_x, cell_global_pos_y);
        if (flag) {
          return flag;
        }
      }
    }
  }

  return false;
}

bool PerformCollideCheckWithSide(Board *p_board, BoardSide board_side, int x,
                                 int y) {
  if (board_side == kBoardSideUp) {
    if (y < 0) {
      return true;
    }
  } else if (board_side == kBoardSideDown) {
    if (y > p_board->height_) {
      return true;
    }
  } else if (board_side == kBoardSideLeft) {
    if (x <= -1) {
      return true;
    }
  } else if (board_side == kBoardSideRight) {
    if (x >= p_board->width_) {
      return true;
    }
  }
  return false;
}
bool PerformFutureCollideCheckWithSide(Board *p_board, BoardSide board_side,
                                       int x, int y) {
  if (board_side == kBoardSideUp) {
    if (y - 1 < 0) {
      return true;
    }
  } else if (board_side == kBoardSideDown) {
    if (y + 1 > p_board->height_) {
      return true;
    }
  } else if (board_side == kBoardSideLeft) {
    if (x - 1 < 0) {
      return true;
    }
  } else if (board_side == kBoardSideRight) {
    if (x + 1 >= p_board->width_) {
      return true;
    }
  }
  return false;
}

bool CheckCollideWithBlocks(Player *p_player, Board *p_board) {
  PlayerBoard *p_player_board = &p_player->board_;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      if (p_player_board->board_[row_index][column_index].is_set_) {
        int cell_global_pos_x = p_player->x_ + column_index;
        int cell_global_pos_y = p_player->y_ + row_index;
        bool flag =
            p_board->cells_[cell_global_pos_y][cell_global_pos_x].is_set_;
        if (flag) {
          return flag;
        }
      }
    }
  }
  return false;
}
bool CheckFutureCollideWithBlocksLeft(Player *p_player, Board *p_board) {
  PlayerBoard *p_player_board = &p_player->board_;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      if (p_player_board->board_[row_index][column_index].is_set_) {
        bool flag = false;
        int cell_global_pos_x = p_player->x_ + column_index - 1;
        int cell_global_pos_y = p_player->y_ + row_index;
        if (cell_global_pos_x < -1 || cell_global_pos_x > 8) {
          flag |= true;
        }
        flag |= p_board->cells_[cell_global_pos_y][cell_global_pos_x].is_set_;
        if (flag) {
          return flag;
        }
      }
    }
  }
  return false;
}
bool CheckFutureCollideWithBlocksRight(Player *p_player, Board *p_board) {
  PlayerBoard *p_player_board = &p_player->board_;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      if (p_player_board->board_[row_index][column_index].is_set_) {
        int cell_global_pos_x = p_player->x_ + column_index + 1;
        int cell_global_pos_y = p_player->y_ + row_index;
        bool flag =
            p_board->cells_[cell_global_pos_y][cell_global_pos_x].is_set_;
        if (flag) {
          return flag;
        }
      }
    }
  }
  return false;
}