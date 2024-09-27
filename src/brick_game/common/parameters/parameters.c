#include "parameters.h"

Parameters *AllocParameters() {
  Parameters *p_parameters = (Parameters *)calloc(sizeof(Parameters), 1);
  p_parameters->t_state_ = AllocState();
  p_parameters->t_game_status_ = AllocGameStatus();
  p_parameters->t_board_ = AllocBoard();
  p_parameters->t_player_ = AllocPlayer();
  p_parameters->t_next_player_ = AllocPlayer();
  p_parameters->t_predict_player_ = AllocPlayer();
  p_parameters->t_records_ = AllocRecords();
  p_parameters->t_last_moved_time_ = (long long *)calloc(sizeof(long long), 1);
  p_parameters->t_username = (char*)calloc(sizeof(char), 20);

  p_parameters->s_state_ = AllocState();
  p_parameters->s_player_ = AllocPlayer();
  p_parameters->s_fruit_ = AllocCell();
  p_parameters->s_game_status_ = AllocGameStatus();
  p_parameters->s_board_ = AllocBoard();
  p_parameters->s_records_ = AllocRecords();
  p_parameters->s_last_moved_time_ = (long long *)calloc(sizeof(long long), 1);
  p_parameters->s_username = (char*)calloc(sizeof(char), 20);

  return p_parameters;
}

void FreeParameters(Parameters *p_parameters){
  FreeState(p_parameters->s_state_);
  FreePlayer(p_parameters->s_player_);
  FreeCell(p_parameters->s_fruit_);
  FreeGameStatus(p_parameters->s_game_status_);
  FreeBoard(p_parameters->s_board_);
  FreeRecords(p_parameters->s_records_);
  free(p_parameters->s_last_moved_time_);
  free(p_parameters->s_username);

  free(p_parameters->t_username);
  free(p_parameters->t_last_moved_time_);
  FreeRecords(p_parameters->t_records_);
  FreePlayer(p_parameters->t_predict_player_);
  FreePlayer(p_parameters->t_next_player_);
  FreePlayer(p_parameters->t_player_);
  FreeBoard(p_parameters->t_board_);
  FreeGameStatus(p_parameters->t_game_status_);
  FreeState(p_parameters->t_state_);
  free(p_parameters);
}