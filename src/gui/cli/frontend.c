#include "frontend.h"

#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../brick_game/snake/controller/controller.h"
#include "../../brick_game/tetris/fsm/fsm.h"

#include "cjson.h"
#include "retrieve_data.h"
#include "draw_objects.h"



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

void HandleCarRacingLoop() {
  char input = 0;

  while (1) {

    cJSON *game_state = GetGameStateFromServer();

    // Extract car racing parameters
    cJSON *car_racing_parameters =
        cJSON_GetObjectItem(game_state, "car_racing_parameters");

    // Draw the game
    DrawCarRacingBoard(car_racing_parameters);

    // Wait for input before exiting
    getch();
    input = GET_USER_INPUT;
    //
    // Convert input into an action and send to server
    if (input == 'w') {
      MakeAction(1);
    }
    else if (input == 's') {
      MakeAction(2);
    } else if (input == 'a') {
      MakeAction(3);
    } else if (input == 'd') {
      MakeAction(4);
    }

    //    // Exit if user presses 'q'
    //    if (input == 'q') {
    //      break;
    //    }
  }
}

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
    if (*p_parameters->t_state_ != kStart &&
        *p_parameters->t_state_ != kPause) {
      PrintTetrisGame(p_parameters);
    }
    if (*p_parameters->t_state_ == kPause) {
      PrintPause();
    }
    if (*p_parameters->t_state_ == kGameOver) {
      GetPlayerName(p_parameters->t_username);
      PrintBegin();
      RemoveRecord(p_parameters->t_records_, "Unnamed",
                   TETRIS_RECORDS_FILE_NAME);
      AddRecord(p_parameters->t_records_, p_parameters->t_username,
                p_parameters->t_game_status_->score_, TETRIS_RECORDS_FILE_NAME);
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

int main(void) {
  WIN_INIT(50);

  setlocale(LC_ALL, "");
  srand(time(NULL));

  GameState state = kGameStateNone;

  const char *options[] = {"Tetris", "Snake", "Car Racing", "Tank Classic",
                           "Exit"};
  int size = sizeof(options) / sizeof(options[0]);

  int choice;

  while (state != kGameStateExit) {
    choice = CreateMenu(options, size);
    if (choice == 0) {
      state = kGameStateTetris;
    } else if (choice == 1) {
      state = kGameStateSnake;
    } else if (choice == 2) {
      state = kGameStateCarRacing;
    } else if (choice == 3) {
      state = kGameStateTankClassic;
    } else {
      state = kGameStateExit;
    }

    if (state == kGameStateTetris) {
      HandleTetrisLoop();
    } else if (state == kGameStateSnake) {
      HandleSnakeLoop();
    } else if (state == kGameStateCarRacing) {
      HandleCarRacingLoop();
    }
  }

  endwin();

  return 0;
}

int CreateMenu(const char *options[], int size) {
  int highlight = 0;
  int choice = -1;
  int key;

  while (1) {
    clear();

    for (int i = 0; i < size; i++) {
      if (i == highlight) {
        attron(A_REVERSE);
      }
      mvprintw(i + 1, 1, "%s", options[i]);
      attroff(A_REVERSE);
    }

    key = getch();

    switch (key) {
    case KEY_UP:
      highlight = (highlight - 1 + size) % size;
      break;
    case KEY_DOWN:
      highlight = (highlight + 1) % size;
      break;
    case 10:
      choice = highlight;
      break;
    }
    if (choice != -1) {
      break;
    }
  }
  return choice;
}
