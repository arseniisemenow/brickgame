#include "frontend.h"

#include "../../brick_game/snake/controller/controller.h"
#include "../../brick_game/tetris/fsm/fsm.h"

#include "cjson.h"
#include "draw_objects.h"
#include "retrieve_data.h"

void SnakeLoop(Parameters *p_parameters) {
  int user_input = 0;
  bool key_held = false;
  bool break_flag = false;

  while (!break_flag) {
    if (*p_parameters->s_state_ == kExitState) {
      break_flag = TRUE;
    }

    SignalType signal = GetSignal(user_input, 0, &key_held);
    ControllerSnake(signal, p_parameters);
    if (*p_parameters->s_state_ != kStart &&
        *p_parameters->s_state_ != kPause) {
      PrintSnakeGame(p_parameters);
    }
    if (*p_parameters->s_state_ == kPause) {
      PrintPause();
    } else if (*p_parameters->s_state_ == kGameOver) {
      GetPlayerName(p_parameters->s_username);
      PrintBegin();
      RemoveRecord(p_parameters->s_records_, "Unnamed",
                   SNAKE_RECORDS_FILE_NAME);
      AddRecord(p_parameters->s_records_, p_parameters->s_username,
                p_parameters->s_game_status_->score_, SNAKE_RECORDS_FILE_NAME);

      *p_parameters->s_state_ = kStart;
    }
    user_input = GET_USER_INPUT;
  }
}

void HandleSnakeLoop() {
  Parameters *parameters = AllocParameters();
  InitBoard(parameters->s_board_);
  InitGameStatus(parameters->s_game_status_);
  InitPlayer(parameters->s_player_);
  SetPlayerPosition(parameters->s_player_, 10, 10);

  parameters->s_player_->snake_length_ = 4;
  parameters->s_player_->direction_ = kDirectionSecond;
  parameters->s_player_->snake_body_[0].x_ = 10 / 2;
  parameters->s_player_->snake_body_[0].y_ = 20 / 2;
  *parameters->s_state_ = kStart;
  InitCell(parameters->s_fruit_);
  // todo: move
  parameters->s_fruit_->y_ = rand() % 10;
  parameters->s_fruit_->x_ = rand() % 20;

  *parameters->s_last_moved_time_ = GetTimeInMS();

  LoadRecords(parameters->s_records_, SNAKE_RECORDS_FILE_NAME);
  SaveRecords(parameters->s_records_, SNAKE_RECORDS_FILE_NAME);

  InitGameColors();
  PrintBegin();
  SnakeLoop(parameters);
}
