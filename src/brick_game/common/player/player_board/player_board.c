#include "player_board.h"

void InitPlayerBoard(PlayerBoard *p_player_board) {
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      InitCell(&p_player_board->board_[i][j]);
    }
  }
}

void CopyPlayerBoard(PlayerBoard *p_player_board_dest,
                     PlayerBoard player_board_src) {
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      CopyCell(&p_player_board_dest->board_[i][j],
               player_board_src.board_[i][j]);
    }
  }
}

void SetPlayerBoardBlock(PlayerBoard *p_player_board, BlockType block_type,
                         Direction block_rotation) {
  BlockColorType block_color_type = GetBlockColor(block_type);
  int mask = 0b1000000000000000;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; row_index++) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         column_index++) {
      p_player_board->board_[row_index][column_index].color_ = block_color_type;
      if (kBlocksBitmask[block_type][block_rotation] & mask) {
        p_player_board->board_[row_index][column_index].is_set_ = true;
      } else {
        InitCell(&p_player_board->board_[row_index][column_index]);
      }
      mask >>= 1;
    }
  }
}