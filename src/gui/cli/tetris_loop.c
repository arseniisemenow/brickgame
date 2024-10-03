#include "frontend.h"

#include "../../brick_game/snake/controller/controller.h"
#include "../../brick_game/tetris/fsm/fsm.h"
#include "draw_objects.h"


void TetrisLoop(Parameters *p_parameters) {
  int user_input = 0;
  bool key_held = false;
  bool break_flag = false;

  while (!break_flag) {
    if (*p_parameters->t_state_ == kExitState) {
      break_flag = TRUE;
    }

    SignalType signal = GetSignal(user_input, 0, &key_held);
    SignalAction(signal, p_parameters);
    if (*p_parameters->t_state_ != kStart) {
      PrintTetrisGame(p_parameters);
    }
    if (*p_parameters->t_state_ == kGameOver) {
      GetPlayerName(p_parameters->t_username);
      PrintBegin();
      RemoveRecord(p_parameters->t_records_, "Unnamed",
                   TETRIS_RECORDS_FILE_NAME);
      AddRecord(p_parameters->t_records_, p_parameters->t_username,
                p_parameters->t_game_status_->score_, TETRIS_RECORDS_FILE_NAME);
      InitGameStatus(p_parameters->t_game_status_); // To solve the tetris desktop bug
    }

    user_input = GET_USER_INPUT;
  }
}

void HandleTetrisLoop() {
  Parameters *p_parameters = AllocParameters();

  InitPlayer(p_parameters->t_player_);
  InitNextPlayer(p_parameters->t_next_player_);
  InitBoard(p_parameters->t_board_);
  InitGameStatus(p_parameters->t_game_status_);

  *p_parameters->t_last_moved_time_ = GetTimeInMS();

  LoadRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);
  SaveRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);

  InitGameColors();
  PrintBegin();
  TetrisLoop(p_parameters);
}
