#include "frontend.h"

#include <unistd.h>

#include "draw_objects.h"
#include "retrieve_data.h"

void CarRacingLoop() {
  int input = 0;
  bool key_held = 0;
  bool break_flag = FALSE;

  SelectGame(3);
  MakeAction(6);

  while (!break_flag) {
    usleep(100000);
    CarRacingParameters game_state = GetGameStateFromServer();
    if (game_state.state_ == kExitState) {
      break_flag = true;
    }
    if (game_state.state_ != kStart && game_state.state_ != kPause) {
      PrintCarRacingGame(&game_state);
    }

    SignalType signal = GetSignal(input, 0, &key_held);

    if (game_state.state_ == kPause) {
      PrintPause();
    }
    MakeAction(signal);
    input = GET_USER_INPUT;
  }
}

void HandleCarRacingLoop() {
  InitGameColors();
  PrintBegin();
  CarRacingLoop();
}
