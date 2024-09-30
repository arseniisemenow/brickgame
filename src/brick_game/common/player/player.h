#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PLAYER_PLAYER_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PLAYER_PLAYER_H_

#include "../block/block.h"
#include "player_board/player_board.h"

#define INIT_PLAYER_POS_X (3)
#define INIT_PLAYER_POS_Y (0)

#define INIT_NEXT_PLAYER_POS_X (16)
#define INIT_NEXT_PLAYER_POS_Y (1)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int x_;
  int y_;
  BlockType block_type_;
  PlayerBoard *board_;
  Cell *snake_body_;
  int snake_length_;
  Direction direction_;
} Player;

Player * AllocPlayer();
void FreePlayer(Player *);

Direction PlayerGetDirection(const Player* player);
int PlayerGetSnakeLength(const Player* player);
Cell* PlayerGetSnakeBodyIndex(const Player* player, const int index);
PlayerBoard* PlayerGetPlayerBoard(const Player* player);
BlockType PlayerGetBlockType(const Player* player);
int PlayerGetX(const Player* player);
int PlayerGetY(const Player* player);




void InitPlayer(Player *p_player);
void InitNextPlayer(Player *p_player);
void CopyPlayer(Player *p_player_dest, const Player *p_player_src);
void InitPlayerPosition(Player *p_player);
void SetPlayerBlockType(Player *p_player, BlockType block_type);
void SetPlayerBlockRotation(Player *p_player, Direction block_rotation);
void SetPlayerNextBlockRotation(Player *p_player);
void SetPlayerPreviousBlockRotation(Player *p_player);
void UpdatePlayerBoard(Player *p_player);
void SetNextPlayerColor(Player *p_player);
void SetPlayerPosition(Player *p_player, int x, int y);
void MovePlayerByDXDY(Player *p_player, int d_x, int d_y);
void MovePlayerUp(Player *p_player);
void MovePlayerDown(Player *p_player);
void MovePlayerLeft(Player *p_player);
void MovePlayerRight(Player *p_player);
#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PLAYER_PLAYER_H_
