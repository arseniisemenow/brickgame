#include "backend.h"

void BoardOverlayBlock(Player *p_player, Board *p_board) {
  PlayerBoard *p_player_board = &p_player->board_;

  int player_pos_x = p_player->x_;
  int player_pos_y = p_player->y_ - 1;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      int cell_global_pos_x = player_pos_x + column_index;
      int cell_global_pos_y = player_pos_y + row_index;
      Cell *p_board_cell =
          &p_board->cells_[cell_global_pos_y][cell_global_pos_x];
      Cell player_cell = p_player_board->board_[row_index][column_index];

      if (player_cell.is_set_) {
        CopyCell(p_board_cell, player_cell);
      }
    }
  }
}

void MovePredictPlayerDown(Player *p_player, Board *p_board) {
  bool break_flag = false;
  while (!break_flag) {
    if (CheckFutureCollideWithDown(p_player, p_board)) {
      break_flag = true;
    }
    if (CheckCollideWithBlocks(p_player, p_board)) {
      break_flag = true;
    }
    if (!break_flag) {
      MovePlayerDown(p_player);
    }
  }
  MovePlayerUp(p_player);
}

void UpdatePredictPlayer(Player *p_player_dest, Player player_src,
                         Board *p_board) {
  CopyPlayer(p_player_dest, player_src);
  MovePredictPlayerDown(p_player_dest, p_board);
  SetNextPlayerColor(p_player_dest);
}

long long int GetTimeStepMS(GameStatus *p_game_status) {
  if (p_game_status->level_ > MAX_LEVEL_COUNT) {
    p_game_status->level_ = MAX_LEVEL_COUNT;
  }
  return kArrayOfTimeStep[p_game_status->level_];
}
