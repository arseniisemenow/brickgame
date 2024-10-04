#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PARAMETERS_PARAMETERS_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PARAMETERS_PARAMETERS_H_

#include <stdlib.h>
#include <utime.h>

#include "../board/board.h"
#include "../fsm_types.h"
#include "../game_status/game_status.h"
#include "../player/player.h"
#include "../records/records.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  struct {
    struct {
      State* t_state_;
      GameStatus* t_game_status_;
      Board* t_board_;
      Player* t_player_;
      Player* t_next_player_;
      Player* t_predict_player_;
      Records* t_records_;
      long long* t_last_moved_time_;
      char* t_username;
    };
    struct {
      State* s_state_;
      Player* s_player_;
      Cell* s_fruit_;
      GameStatus* s_game_status_;
      Board* s_board_;
      Records* s_records_;
      long long* s_last_moved_time_;
      char* s_username;  // size is 20 btw
    };
  };

} Parameters;

typedef struct {
  int lane_;
  int y_;
} Car;

typedef struct {
  int state_;
  int score_;
  int level_;
  int record_score_;
  Car player_car_racing_;
  Car rival_cars_[2];
  int track_height_;
  int track_width_;
  int time_step_;
  int last_moved_time_;
} CarRacingParameters;

Parameters* AllocParameters();
void FreeParameters(Parameters* p_parameters);

void InitParametersTetris(Parameters* p_parameters);
void InitParametersSnake(Parameters* p_parameters);

char* AllocUsername();
long long* AllocLastMovedTime();
void FreeUsername(char* username);
void FreeLastMovedTime(long long* last_move_time);

State* GetTState(Parameters* p_parameters);
State GetTStateValue(Parameters* p_parameters);

GameStatus* GetTGameStatus(Parameters* p_parameters);
Board* GetTBoard(Parameters* p_parameters);
int** GetTBoardBoard(Parameters* p_parameters);
Player* GetTPlayer(Parameters* p_parameters);
Player* GetTNextPlayer(Parameters* p_parameters);
Player* GetTPredictPlayer(Parameters* p_parameters);
Records* GetTRecords(Parameters* p_parameters);
long long* GetTLastMoveTime(Parameters* p_parameters);
char* GetTUserName(Parameters* p_parameters);

State* GetSState(Parameters* p_parameters);
State GetSStateValue(Parameters* p_parameters);
GameStatus* GetSGameStatus(Parameters* p_parameters);
Board* GetSBoard(Parameters* p_parameters);
int** GetSBoardBoard(Parameters* p_parameters);
Player* GetSPlayer(Parameters* p_parameters);
Records* GetSRecords(Parameters* p_parameters);
long long* GetSLastMoveTime(Parameters* p_parameters);
char* GetSUserName(Parameters* p_parameters);
Cell* GetSFruit(Parameters* p_parameters);

#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_PARAMETERS_PARAMETERS_H_
