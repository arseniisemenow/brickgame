// #include "../../src/brick_game/tetris/backend/backend.h"
#include "../../src/brick_game/tetris/fsm/fsm.h"
#include <assert.h>
#include <printf.h>


int main() {
  Parameters *p_parameters = AllocParameters();
  InitPlayer(p_parameters->t_player_);
  InitBoard(p_parameters->t_board_);
  PrintPlayerBoard(p_parameters->t_player_->board_);
  SetPlayerNextBlockRotation(p_parameters->t_player_);
  PrintPlayerBoard(p_parameters->t_player_->board_);
  if (CheckCollide(p_parameters->t_player_, p_parameters->t_board_)) {
    SetPlayerPreviousBlockRotation(p_parameters->t_player_);
  }
  UpdatePredictPlayer(p_parameters->t_predict_player_, p_parameters->t_player_,
                      p_parameters->t_board_);
  CheckCollisions(p_parameters);
}