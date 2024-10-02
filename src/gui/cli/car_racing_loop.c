#include "frontend.h"

#include <unistd.h>

#include "../../brick_game/common/retrieve_data/retrieve_data.h"
#include "draw_objects.h"

void CarRacingLoop() {
  int input = 0;
  bool key_held = 0;
  bool break_flag = FALSE;

  int error_code = SelectGame(3);
  if (error_code) {
    return;
  }

  //  MakeAction(6); // If wanna skip spawn state at the beginning

  while (!break_flag && !error_code) {
    usleep(10000);
    CarRacingParameters game_state = GetGameStateFromServer();
    if (game_state.state_ == kExitState) {
      break_flag = true;
    }
    if (game_state.state_ != kStart) {
      PrintCarRacingGame(&game_state);
    }
    if (game_state.state_ == kGameOver) {
      PrintBegin();
    }

    SignalType signal = GetSignal(input, 0, &key_held);

    error_code = MakeAction(signal);
    input = GET_USER_INPUT;
  }
}

void HandleCarRacingLoop() {
  InitGameColors();
  PrintBegin();
  CarRacingLoop();
}
