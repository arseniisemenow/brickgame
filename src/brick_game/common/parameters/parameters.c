#include "parameters.h"

#include <stdio.h>

#include "../time_handler/time_handler.h"

char* AllocUsername() {
  char* username = (char*)calloc(sizeof(char), 20);
  return username;
}

void FreeUsername(char* username) { free(username); }
long long* AllocLastMovedTime() {
  long long* last_moved_time = (long long*)calloc(sizeof(long long), 1);
  return last_moved_time;
}

void FreeLastMovedTime(long long* last_move_time) { free(last_move_time); }

Parameters* AllocParameters() {
  Parameters* p_parameters = (Parameters*)calloc(sizeof(Parameters), 1);
  p_parameters->t_state_ = AllocState();
  p_parameters->t_game_status_ = AllocGameStatus();
  p_parameters->t_board_ = AllocBoard();
  p_parameters->t_player_ = AllocPlayer();
  p_parameters->t_next_player_ = AllocPlayer();
  p_parameters->t_predict_player_ = AllocPlayer();
  p_parameters->t_records_ = AllocRecords();
  p_parameters->t_last_moved_time_ = AllocLastMovedTime();
  p_parameters->t_username = AllocUsername();

  p_parameters->s_state_ = AllocState();
  p_parameters->s_player_ = AllocPlayer();
  p_parameters->s_fruit_ = AllocCell();
  p_parameters->s_game_status_ = AllocGameStatus();
  p_parameters->s_board_ = AllocBoard();
  p_parameters->s_records_ = AllocRecords();
  p_parameters->s_last_moved_time_ = AllocLastMovedTime();
  p_parameters->s_username = AllocUsername();

  return p_parameters;
}

void FreeParameters(Parameters* p_parameters) {
  FreeState(p_parameters->s_state_);
  FreePlayer(p_parameters->s_player_);
  FreeCell(p_parameters->s_fruit_);
  FreeGameStatus(p_parameters->s_game_status_);
  FreeBoard(p_parameters->s_board_);
  FreeRecords(p_parameters->s_records_);
  FreeLastMovedTime(p_parameters->s_last_moved_time_);
  FreeUsername(p_parameters->s_username);

  FreeUsername(p_parameters->t_username);
  FreeLastMovedTime(p_parameters->t_last_moved_time_);
  FreeRecords(p_parameters->t_records_);
  FreePlayer(p_parameters->t_predict_player_);
  FreePlayer(p_parameters->t_next_player_);
  FreePlayer(p_parameters->t_player_);
  FreeBoard(p_parameters->t_board_);
  FreeGameStatus(p_parameters->t_game_status_);
  FreeState(p_parameters->t_state_);
  free(p_parameters);
}

State* GetTState(Parameters* p_parameters) { return p_parameters->t_state_; }
State GetTStateValue(Parameters* p_parameters) {
  return *p_parameters->t_state_;
}
GameStatus* GetTGameStatus(Parameters* p_parameters) {
  return p_parameters->t_game_status_;
}
Board* GetTBoard(Parameters* p_parameters) { return p_parameters->t_board_; }

Player* GetTPlayer(Parameters* p_parameters) { return p_parameters->t_player_; }
Player* GetTNextPlayer(Parameters* p_parameters) {
  return p_parameters->t_next_player_;
}
Player* GetTPredictPlayer(Parameters* p_parameters) {
  return p_parameters->t_predict_player_;
}
Records* GetTRecords(Parameters* p_parameters) {
  return p_parameters->t_records_;
}
long long* GetTLastMoveTime(Parameters* p_parameters) {
  return p_parameters->t_last_moved_time_;
}
char* GetTUserName(Parameters* p_parameters) {
  return p_parameters->t_username;
}

State* GetSState(Parameters* p_parameters) { return p_parameters->s_state_; }
State GetSStateValue(Parameters* p_parameters) {
  return *p_parameters->s_state_;
}
GameStatus* GetSGameStatus(Parameters* p_parameters) {
  return p_parameters->s_game_status_;
}
Board* GetSBoard(Parameters* p_parameters) { return p_parameters->s_board_; }

Player* GetSPlayer(Parameters* p_parameters) { return p_parameters->s_player_; }
Records* GetSRecords(Parameters* p_parameters) {
  return p_parameters->s_records_;
}
long long* GetSLastMoveTime(Parameters* p_parameters) {
  return p_parameters->s_last_moved_time_;
}
char* GetSUserName(Parameters* p_parameters) {
  return p_parameters->s_username;
}

Cell* GetSFruit(Parameters* p_parameters) { return p_parameters->s_fruit_; }

void InitParametersTetris(Parameters* p_parameters) {
  *p_parameters->t_state_ = kStart;
  InitPlayer(p_parameters->t_player_);
  InitNextPlayer(p_parameters->t_next_player_);
  InitBoard(p_parameters->t_board_);
  InitGameStatus(p_parameters->t_game_status_);

  *p_parameters->t_last_moved_time_ = GetTimeInMS();

  LoadRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);
  SaveRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);
}

void InitParametersSnake(Parameters* p_parameters) {
  *p_parameters->s_state_ = kStart;
  InitBoard(p_parameters->s_board_);
  InitGameStatus(p_parameters->s_game_status_);
  InitPlayer(p_parameters->s_player_);
  SetPlayerPosition(p_parameters->s_player_, 10, 10);  // Do I need this?

  p_parameters->s_player_->snake_length_ = 4;
  p_parameters->s_player_->direction_ = kDirectionSecond;
  p_parameters->s_player_->snake_body_[0].x_ = 10 / 2;
  p_parameters->s_player_->snake_body_[0].y_ = 20 / 2;
  *p_parameters->s_state_ = kStart;
  InitCell(p_parameters->s_fruit_);
  // todo: move
  p_parameters->s_fruit_->y_ = rand() % 10;
  p_parameters->s_fruit_->x_ = rand() % 20;

  *p_parameters->s_last_moved_time_ = GetTimeInMS();

  LoadRecords(p_parameters->s_records_, SNAKE_RECORDS_FILE_NAME);
  SaveRecords(p_parameters->s_records_, SNAKE_RECORDS_FILE_NAME);
}
