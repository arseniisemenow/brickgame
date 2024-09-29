#include "parameters.h"
#include "../time_handler/time_handler.h"
#include <stdio.h>

char* AllocUsername(){
    char* username =(char*)calloc(sizeof(char), 20);
    return username;
}

void FreeUsername(char*username){
    free (username);
}
long long * AllocLastMovedTime(){
    long long * last_moved_time =(long long*)calloc(sizeof(long long ), 1);
    return last_moved_time;
}

void FreeLastMovedTime(long long* last_move_time){
    free(last_move_time);
}

Parameters *AllocParameters() {
  Parameters *p_parameters = (Parameters *)calloc(sizeof(Parameters), 1);
  p_parameters->t_state_ = AllocState();
  p_parameters->t_game_status_ = AllocGameStatus();
  p_parameters->t_board_ = AllocBoard();
  p_parameters->t_player_ = AllocPlayer();
  p_parameters->t_next_player_ = AllocPlayer();
  p_parameters->t_predict_player_ = AllocPlayer();
  p_parameters->t_records_ = AllocRecords();
  p_parameters->t_last_moved_time_ = AllocLastMovedTime();
  p_parameters->t_username = AllocUsername();

//  p_parameters->s_state_ = AllocState();
//  p_parameters->s_player_ = AllocPlayer();
//  p_parameters->s_fruit_ = AllocCell();
//  p_parameters->s_game_status_ = AllocGameStatus();
//  p_parameters->s_board_ = AllocBoard();
//  p_parameters->s_records_ = AllocRecords();
//  p_parameters->s_last_moved_time_ = (long long *)calloc(sizeof(long long), 1);
//  p_parameters->s_username = (char*)calloc(sizeof(char), 20);

  return p_parameters;
}

void FreeParameters(Parameters *p_parameters){
  FreeState(p_parameters->s_state_);
  FreePlayer(p_parameters->s_player_);
  FreeCell(p_parameters->s_fruit_);
  FreeGameStatus(p_parameters->s_game_status_);
  FreeBoard(p_parameters->s_board_);
  FreeRecords(p_parameters->s_records_);
  FreeLastMovedTime(p_parameters->s_last_moved_time_);
  FreeUsername(p_parameters->s_username);
//
//  free(p_parameters->t_username);
//  free(p_parameters->t_last_moved_time_);
//  FreeRecords(p_parameters->t_records_);
//  FreePlayer(p_parameters->t_predict_player_);
//  FreePlayer(p_parameters->t_next_player_);
//  FreePlayer(p_parameters->t_player_);
//  FreeBoard(p_parameters->t_board_);
//  FreeGameStatus(p_parameters->t_game_status_);
//  FreeState(p_parameters->t_state_);
  free(p_parameters);
}

State * GetTState(Parameters* p_parameters){
    return p_parameters->t_state_;
}
State GetTStateValue(Parameters* p_parameters){
    return *p_parameters->t_state_;
}
GameStatus * GetTGameStatus(Parameters* p_parameters){
  return p_parameters->t_game_status_;
}
Board * GetTBoard(Parameters* p_parameters){
    return p_parameters->t_board_;
}
Player * GetTPlayer(Parameters* p_parameters){
    return p_parameters->t_player_;
}
Player * GetTNextPlayer(Parameters* p_parameters){
    return p_parameters->t_next_player_;
}
Player * GetTPredictPlayer(Parameters* p_parameters){
    return p_parameters->t_predict_player_;
}
Records * GetTRecords(Parameters* p_parameters){
    return p_parameters->t_records_;
}
long long * GetTLastMoveTime(Parameters* p_parameters){
    return p_parameters->t_last_moved_time_;
}
char * GetTUserName(Parameters* p_parameters){
    return p_parameters->t_username;
}
void InitParametersTetris(Parameters* p_parameters){
    fprintf(stderr, "InitParametersTetris is called\n");
    InitPlayer(p_parameters->t_player_);
    InitNextPlayer(p_parameters->t_next_player_);
    InitBoard(p_parameters->t_board_);
    InitGameStatus(p_parameters->t_game_status_);

    *p_parameters->t_last_moved_time_ = GetTimeInMS();

    LoadRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);
    SaveRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);
}


