#include "parameters.h"

Parameters *AllocParameters() {
  Parameters *parameters = (Parameters *)calloc(sizeof(Parameters), 1);
  parameters->t_state_ = AllocState();
  parameters->t_game_status_ = AllocGameStatus();
  parameters->t_board_ = AllocBoard();
  parameters->t_player_ = AllocPlayer();
  parameters->t_next_player_ = AllocPlayer();
  parameters->t_predict_player_ = AllocPlayer();
  parameters->t_records_ = AllocRecords();
  parameters->t_last_moved_time_ = calloc(sizeof(long long), 1);
  parameters->t_username = calloc(sizeof(char), 20);
  return parameters;
}

void FreeParameters(Parameters *p_parameters){
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