#include "collisions_checker.h"

#include <printf.h>

bool CheckFutureCollideWithUp(const Player *p_player, const Board *p_board) {
  return CheckFutureCollideWithSide(p_player, p_board, kBoardSideUp);
}
bool CheckFutureCollideWithDown(const Player *p_player, const Board *p_board) {
  return CheckFutureCollideWithSide(p_player, p_board, kBoardSideDown);
}
bool CheckFutureCollideWithLeft(const Player *p_player, const Board *p_board) {
  return CheckFutureCollideWithSide(p_player, p_board, kBoardSideLeft);
}
bool CheckFutureCollideWithRight(const Player *p_player, const Board *p_board) {
  return CheckFutureCollideWithSide(p_player, p_board, kBoardSideRight);
}

bool CheckCollideWithUp(const Player *p_player, const Board *p_board) {
  return CheckCollideWithSide(p_player, p_board, kBoardSideUp);
}
bool CheckCollideWithDown(const Player *p_player, const Board *p_board) {
  return CheckCollideWithSide(p_player, p_board, kBoardSideDown);
}
bool CheckCollideWithLeft(const Player *p_player, const Board *p_board) {
  return CheckCollideWithSide(p_player, p_board, kBoardSideLeft);
}
bool CheckCollideWithRight(const Player *p_player, const Board *p_board) {
  return CheckCollideWithSide(p_player, p_board, kBoardSideRight);
}

bool CheckCollide(const Player *p_player, const Board *p_board) {
  bool flag = CheckCollideWithUp(p_player, p_board);
  flag |= CheckCollideWithDown(p_player, p_board);
  flag |= CheckCollideWithLeft(p_player, p_board);
  flag |= CheckCollideWithRight(p_player, p_board);
  flag |= CheckCollideWithBlocks(p_player, p_board);
  return flag;
}

bool CheckCollideWithSide(const Player *p_player, const Board *p_board,
                          const BoardSide board_side) {
  PlayerBoard *p_player_board = p_player->board_;
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

bool CheckFutureCollideWithSide(const Player *p_player, const Board *p_board,
                                const BoardSide board_side) {
  PlayerBoard *p_player_board = p_player->board_;
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

bool PerformCollideCheckWithSide(const Board *p_board,
                                 const BoardSide board_side, const int x,
                                 const int y) {
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
bool PerformFutureCollideCheckWithSide(const Board *p_board,
                                       const BoardSide board_side, const int x,
                                       const int y) {
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

bool CheckCollideWithBlocks(const Player *p_player, const Board *p_board) {
  PlayerBoard *p_player_board = p_player->board_;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      if (p_player_board->board_[row_index][column_index].is_set_) {
        int cell_global_pos_x = p_player->x_ + column_index;
        int cell_global_pos_y = p_player->y_ + row_index;
        if (cell_global_pos_y > 19 ||
            cell_global_pos_x > 9) {  // skip out of the bounds
          continue;
        }
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
  PlayerBoard *p_player_board = p_player->board_;

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
        if (cell_global_pos_y < -1 || cell_global_pos_x > 18) {
          flag |= true;
        }
        if (flag) {
          return flag;
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
  PlayerBoard *p_player_board = p_player->board_;

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