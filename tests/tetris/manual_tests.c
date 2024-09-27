#include "../../src/brick_game/tetris/backend/backend.h"

int main(){
  Player* player = {0};
  Board *board = {0};
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBlockRotation(player, kDirectionFirst);
  bool flag = CheckFutureCollideWithBlocksLeft(player, board);
}