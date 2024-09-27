#include "player_board.h"
#include <printf.h>
#include <stdlib.h>

PlayerBoard * AllocPlayerBoard(){
  PlayerBoard *p_player_board = (PlayerBoard*)calloc(sizeof(PlayerBoard), 1);
  p_player_board->board_ = (Cell**)calloc(sizeof(Cell*), PLAYER_BOARD_SIZE);
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    p_player_board->board_[i] = (Cell*)calloc(sizeof(Cell), PLAYER_BOARD_SIZE);
  }
  return p_player_board;
}
void FreePlayerBoard(PlayerBoard *p_player_board){
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    free(p_player_board->board_[i]);
  }
  free(p_player_board->board_);
  free(p_player_board);
}

void InitPlayerBoard(PlayerBoard *p_player_board) {
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      InitCell(&p_player_board->board_[i][j]);
    }
  }
}

void PrintPlayerBoard(const PlayerBoard *p_player_board) {
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    printf("%d", p_player_board->board_[i][0].is_set_);
    for (int j = 1; j < PLAYER_BOARD_SIZE; ++j) {
      printf(" %d", p_player_board->board_[i][j].is_set_);
    }
    printf("\n");
  }
}

void CopyPlayerBoard(PlayerBoard *p_player_board_dest,
                     const PlayerBoard *p_player_board_src) {
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      CopyCell(&p_player_board_dest->board_[i][j],
               p_player_board_src->board_[i][j]);
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