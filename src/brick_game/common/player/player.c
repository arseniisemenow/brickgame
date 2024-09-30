#include "player.h"
#include <stdlib.h>
#include <string.h>

Player *AllocPlayer() {
  Player *p_player = (Player *)calloc(sizeof(Player), 1);
  p_player->board_ = AllocPlayerBoard();
  p_player->snake_body_ = (Cell *)calloc(sizeof(Cell), 200);
  return p_player;
}
void FreePlayer(Player *p_player) { free(p_player); }

Direction PlayerGetDirection(const Player* player){
  return player->direction_;
}
int PlayerGetSnakeLength(const Player* player){
  return player->snake_length_;
}
Cell* PlayerGetSnakeBodyIndex(const Player* player, const int index){
  return &player->snake_body_[index];
}
PlayerBoard* PlayerGetPlayerBoard(const Player* player){
  return player->board_;
}
BlockType PlayerGetBlockType(const Player* player){
  return player->block_type_;
}
int PlayerGetX(const Player* player){
  return player->x_;
}
int PlayerGetY(const Player* player){
  return player->y_;
}


void InitPlayer(Player *p_player) {
  InitPlayerBoard(p_player->board_);
  SetPlayerBlockType(p_player, GetRandomBlockType());
  SetPlayerBoardBlock(p_player->board_, p_player->block_type_, p_player->direction_);
}

void InitNextPlayer(Player *p_player) {
  InitPlayer(p_player);
  p_player->x_ = INIT_NEXT_PLAYER_POS_X;
  p_player->y_ = INIT_NEXT_PLAYER_POS_Y;
  SetPlayerBoardBlock(p_player->board_, p_player->block_type_, kDirectionFirst);
}

void InitPlayerPosition(Player *p_player) {
  p_player->x_ = INIT_PLAYER_POS_X;
  p_player->y_ = INIT_PLAYER_POS_Y;
  p_player->block_type_ = kBlockSnake;
  p_player->direction_ = kDirectionForth;
  //    p_player->snake_body_[0] =
  //    p_player->t_board_.t_board_[p_player->y_][p_player->x_];
}

void CopyPlayer(Player *p_player_dest, const Player *p_player_src) {
  p_player_dest->x_ = p_player_src->x_;
  p_player_dest->y_ = p_player_src->y_;
  p_player_dest->block_type_ = p_player_src->block_type_;
  p_player_dest->direction_ = p_player_src->direction_;
//  p_player_dest->board_ = p_player_src->board_;

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      p_player_dest->board_->board_[i][j] = p_player_src->board_->board_[i][j];
    }
  }

  //  memcpy(p_player_dest->board_->board_, player_src.board_->board_,
  //  sizeof(Cell) * PLAYER_BOARD_SIZE * PLAYER_BOARD_SIZE);
}

void SetPlayerBlockType(Player *p_player, BlockType block_type) {
  p_player->block_type_ = block_type;
//  UpdatePlayerBoard(p_player);
}

void SetPlayerBlockRotation(Player *p_player, Direction block_rotation) {
  p_player->direction_ = block_rotation;
//  SetPlayerBoardBlock(p_player->board_, p_player->block_type_, block_rotation);
//  UpdatePlayerBoard(p_player);
}

void SetPlayerPosition(Player *p_player, int x, int y) {
  p_player->x_ = x;
  p_player->y_ = y;
}

void SetPlayerNextBlockRotation(Player *p_player) {
  Direction block_rotation = p_player->direction_;

  Direction next_block_rotation = GetNextBlockRotation(block_rotation);

  SetPlayerBlockRotation(p_player, next_block_rotation);
  SetPlayerBoardBlock(p_player->board_, p_player->block_type_,
                      p_player->direction_);
}

void SetPlayerPreviousBlockRotation(Player *p_player) {
  Direction block_rotation = p_player->direction_;

  Direction previous_block_rotation = GetPreviousBlockRotation(block_rotation);

  SetPlayerBlockRotation(p_player, previous_block_rotation);
  SetPlayerBoardBlock(p_player->board_, p_player->block_type_,
                      p_player->direction_);
}

void UpdatePlayerBoard(Player *p_player) {
  SetPlayerBoardBlock(p_player->board_, p_player->block_type_, kDirectionFirst);
}

void MovePlayerByDXDY(Player *p_player, int d_x, int d_y) {
  p_player->x_ += d_x;
  p_player->y_ += d_y;
}

void MovePlayerUp(Player *p_player) { MovePlayerByDXDY(p_player, 0, -1); }
void MovePlayerDown(Player *p_player) { MovePlayerByDXDY(p_player, 0, 1); }
void MovePlayerLeft(Player *p_player) { MovePlayerByDXDY(p_player, -1, 0); }
void MovePlayerRight(Player *p_player) { MovePlayerByDXDY(p_player, 1, 0); }

void SetNextPlayerColor(Player *p_player) {
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (p_player->board_->board_[i][j].is_set_) {
        p_player->board_->board_[i][j].color_ = kBlockColorPredict;
      }
    }
  }
}