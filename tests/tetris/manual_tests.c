#include "../../src/brick_game/tetris/backend/backend.h"

int main(){
  Player* player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBlockRotation(player, kDirectionFirst);
  bool flag = CheckCollide(player, board);
}