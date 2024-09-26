#include "frontend.h"

#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../../brick_game/snake/controller/controller.h"
#include "../../brick_game/tetris/fsm/fsm.h"

void PrintTetrisOverlay(void) {
  PrintRectangle(0, BOARD_HEIGHT + 1, 0, BOARD_WIDTH + 1);
  PrintRectangle(0, BOARD_HEIGHT + 1, BOARD_WIDTH + 2,
                 BOARD_WIDTH + HUD_WIDTH + 3);

  PrintRectangle(1, 6, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);

  PrintRectangle(7, 9, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);
  PrintRectangle(10, 12, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);

  MVPRINTW(1, BOARD_WIDTH + 5, "Next");
  MVPRINTW(7, BOARD_WIDTH + 5, "Score");
  MVPRINTW(10, BOARD_WIDTH + 5, "Level");
}
void PrintSnakeOverlay(void) {
  PrintRectangle(0, BOARD_HEIGHT + 1, 0, BOARD_WIDTH + 1);
  PrintRectangle(0, BOARD_HEIGHT + 1, BOARD_WIDTH + 2,
                 BOARD_WIDTH + HUD_WIDTH + 3);

  PrintRectangle(1, 3, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);
  PrintRectangle(4, 6, BOARD_WIDTH + 3, BOARD_WIDTH + HUD_WIDTH + 2);

  MVPRINTW(1, BOARD_WIDTH + 5, "Score");
  MVPRINTW(4, BOARD_WIDTH + 5, "Level");
}

void PrintUserNamePrompt() {
  PrintRectangle(BOARD_HEIGHT / 2 - 5, BOARD_HEIGHT / 2 + 5, BOARDS_BEGIN,
                 BOARDS_BEGIN + BOARD_WIDTH * 2);
  for (int i = BOARD_HEIGHT / 2 - 5 + 1; i < BOARD_HEIGHT / 2 - 5 + 1 + 9;
       ++i) {
    for (int j = BOARDS_BEGIN + 1; j < BOARDS_BEGIN + 1 + 19; ++j) {
      MVPRINTW(i, j, " ");
    }
  }

  MVPRINTW(7, 5, "Enter your name:");
}

void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i_2 = top_y + 1; i_2 < bottom_y; i_2++) {
    MVADDCH(i_2, left_x, ACS_VLINE);
    MVADDCH(i_2, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void PrintTetrisGameStatus(GameStatus *p_game_status) {
  MVPRINTW(8, BOARD_WIDTH + 5, "%7d", p_game_status->score_);
  MVPRINTW(11, BOARD_WIDTH + 5, "%7d", p_game_status->level_);
}
void PrintSnakeGameStatus(GameStatus *p_game_status) {
  MVPRINTW(2, BOARD_WIDTH + 5, "%7d", p_game_status->score_);
  MVPRINTW(5, BOARD_WIDTH + 5, "%7d", p_game_status->level_);
}

void ClearGame() {
  for (int row_index = 0; row_index < 24; ++row_index) {
    for (int column_index = 0; column_index < 28; ++column_index) {
      attron(COLOR_PAIR(INIT_COLOR_PAIR));
      mvprintw(row_index + 1, column_index + 1, " ");
      attroff(COLOR_PAIR(INIT_COLOR_PAIR));
    }
  }
}

void PrintTetrisGame(Parameters *p_parameters) {
  ClearGame();
  PrintTetrisOverlay();
  PrintBoard(p_parameters->t_board_);
  PrintTetrisGameStatus(p_parameters->t_game_status_);
  PrintRecords(13, p_parameters->t_records_);
  PrintBlock(p_parameters->t_predict_player_);
  PrintBlock(p_parameters->t_player_);
  PrintBlock(p_parameters->t_next_player_);
}

void PrintSnakeGame(Parameters *p_parameters) {
  ClearGame();
  PrintSnakeOverlay();
  PrintRecords(7, p_parameters->s_records_);
  PrintSnakeGameStatus(p_parameters->s_game_status_);
  PrintSnakeAndFruit(p_parameters);
}

void PrintSnakeAndFruit(Parameters *p_parameters) {
  for (int y = 0; y < p_parameters->s_board_->height_; ++y) {
    for (int x = 0; x < p_parameters->s_board_->width_; ++x) {
      bool is_snake_body = false;
      for (int i = 0; i < p_parameters->s_player_->snake_length_; ++i) {
        if (p_parameters->s_player_->snake_body_[i].x_ == x &&
            p_parameters->s_player_->snake_body_[i].y_ == y) {
          attron(COLOR_PAIR(GREEN_COLOR_PAIR_INDEX));
          mvprintw(y + BOARDS_BEGIN + 1, x + BOARDS_BEGIN + 1, "S");
          attroff(COLOR_PAIR(GREEN_COLOR_PAIR_INDEX));

          is_snake_body = true;
          break;
        }
      }
      if (!is_snake_body && x == p_parameters->s_fruit_->x_ &&
          y == p_parameters->s_fruit_->y_) {
        attron(COLOR_PAIR(RED_COLOR_PAIR_INDEX));
        mvprintw(y + BOARDS_BEGIN + 1, x + BOARDS_BEGIN + 1, "*");
        attroff(COLOR_PAIR(RED_COLOR_PAIR_INDEX));
      }
      if (is_snake_body && x == p_parameters->s_fruit_->x_ &&
          y == p_parameters->s_fruit_->y_) {
        attron(COLOR_PAIR(PREDICT_COLOR_PAIR_INDEX));
        mvprintw(y + BOARDS_BEGIN + 1, x + BOARDS_BEGIN + 1, "*");
        attroff(COLOR_PAIR(PREDICT_COLOR_PAIR_INDEX));
      }
    }
  }
}

void PrintBoard(Board *p_board) {
  for (int row_index = 0; row_index < 20; ++row_index) {
    for (int column_index = 0; column_index < 10; ++column_index) {
      if (p_board->cells_[row_index][column_index].is_set_) {
        int color = p_board->cells_[row_index][column_index].color_;
        attron(COLOR_PAIR(kBlockColorPairsArray[color]));
        mvprintw(row_index + BOARDS_BEGIN + 1, column_index + BOARDS_BEGIN + 1,
                 "S");
        attroff(COLOR_PAIR(kBlockColorPairsArray[color]));
      } else {
        attron(COLOR_PAIR(INIT_COLOR_PAIR));
        mvprintw(row_index + BOARDS_BEGIN + 1, column_index + BOARDS_BEGIN + 1,
                 " ");
        attroff(COLOR_PAIR(INIT_COLOR_PAIR));
      }
    }
  }
}

void PrintBlock(Player *p_player) {
  int player_pos_x = p_player->x_;
  int player_pos_y = p_player->y_;
  PlayerBoard player_board = p_player->board_;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      int print_y = player_pos_y + BOARDS_BEGIN + 1 + row_index;
      int print_x = player_pos_x + BOARDS_BEGIN + 1 + column_index;
      if (player_board.board_[row_index][column_index].is_set_) {
        int color = player_board.board_[row_index][column_index].color_;
        attron(COLOR_PAIR(kBlockColorPairsArray[color]));
        mvprintw(print_y, print_x, "F");
        attroff(COLOR_PAIR(kBlockColorPairsArray[color]));
      }
    }
  }
}

void GetPlayerName(char str[]) {
  PrintUserNamePrompt();
  int ch;
  int i = 0;

  flushinp();

  refresh();
  while ((ch = getch()) != '\n') {
    if (ch == ERR) {
      continue;
    } else if (ch == KEY_BACKSPACE || ch == DELETE) {
      if (i > 0) {
        i--;
        str[i] = '\0';
        mvprintw(12, 6, "%*s", MAX_LENGTH_NAME + 8, " ");
        mvprintw(12, 6, "%s", str);
        move(MAX_LENGTH_NAME, 6 + i);
        refresh();
      }
    } else if (i < MAX_LENGTH_NAME - 1 && isprint(ch)) {
      str[i++] = ch;
      str[i] = '\0';
      mvprintw(12, 6, "%s", str);
      refresh();
    }
  }
  getch();
}

void PrintBegin() {
  ClearGame();

  PrintRectangle(0, BOARDS_BEGIN + BOARD_HEIGHT - 1, 0,
                 BOARDS_BEGIN + BOARD_WIDTH + HUD_WIDTH + 1);
  mvprintw(11, 6, "Press Enter to play");

  mvprintw(13, 6, "Press Esc to choose");
  mvprintw(14, 10, "another game");
}

void PrintPause() {
  PrintRectangle(0 + 8, BOARDS_BEGIN + BOARD_HEIGHT - 1 - 8, 0 + 4,
                 BOARDS_BEGIN + BOARD_WIDTH + HUD_WIDTH + 1 - 4);
  for (int i = 11; i < 15; ++i) {
    for (int j = 7; j < 23; ++j) {
      mvprintw(i, j, " ");
    }
  }
  mvprintw(12, 8, "Game is paused");
}

void ClearRecords() {}

void PrintRecords(int shift, Records *p_records) {
  ClearRecords();
  PrintRectangle(shift, 20, 13, 24);
  mvprintw(shift + 2, 16, "Records");

  attron(COLOR_PAIR(RECORD_1_COLOR_PAIR_INDEX));
  mvprintw(shift + 3, 16, "1. %7d", p_records->records_[0].score_);
  attron(COLOR_PAIR(RECORD_1_COLOR_PAIR_INDEX));
  attron(COLOR_PAIR(RECORD_2_COLOR_PAIR_INDEX));
  mvprintw(shift + 4, 16, "2. %7d", p_records->records_[1].score_);
  attroff(COLOR_PAIR(RECORD_2_COLOR_PAIR_INDEX));
  attron(COLOR_PAIR(RECORD_3_COLOR_PAIR_INDEX));
  mvprintw(shift + 5, 16, "3. %7d", p_records->records_[2].score_);
  attroff(COLOR_PAIR(RECORD_3_COLOR_PAIR_INDEX));

  attron(COLOR_PAIR(RECORD_4_5_COLOR_PAIR_INDEX));
  mvprintw(shift + 6, 16, "4. %7d", p_records->records_[3].score_);
  attroff(COLOR_PAIR(RECORD_4_5_COLOR_PAIR_INDEX));
  attron(COLOR_PAIR(RECORD_4_5_COLOR_PAIR_INDEX));
  mvprintw(shift + 7, 16, "5. %7d", p_records->records_[4].score_);
  attroff(COLOR_PAIR(RECORD_4_5_COLOR_PAIR_INDEX));
}

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
  Board board = {0};
  InitBoard(&board);

  GameStatus game_status = {0};
  InitGameStatus(&game_status);

  Player player = {0};
  InitPlayer(&player);
  SetPlayerPosition(&player, 10, 10);
  //    InitSnake(&player);
  player.snake_length_ = 4;
  player.direction_ = kDirectionSecond;
  player.snake_body_[0].x_ = 10 / 2;
  player.snake_body_[0].y_ = 20 / 2;

  State state = kStart;
  Records records = {0};

  Cell fruit = {0};
  InitCell(&fruit);
  fruit.y_ = rand() % 10;
  fruit.x_ = rand() % 20;

  long long time_in_secs;
  time_in_secs = GetTimeInMS();

  Parameters parameters = {0};

  parameters.s_state_ = &state;
  parameters.s_player_ = &player;
  parameters.s_fruit_ = &fruit;
  parameters.s_game_status_ = &game_status;
  parameters.s_board_ = &board;
  parameters.s_records_ = &records;
  parameters.s_last_moved_time_ = &time_in_secs;
  LoadRecords(parameters.s_records_, SNAKE_RECORDS_FILE_NAME);
  SaveRecords(parameters.s_records_, SNAKE_RECORDS_FILE_NAME);

  InitGameColors();
  PrintBegin();
  SnakeLoop(&parameters);
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
  Board board = {0};
  GameStatus game_status = {0};
  Player player = {0};
  Player next_player = {0};
  Player predict_player = {0};
  State state = kStart;
  Records records = {0};
  Parameters parameters = {0};
  long long time_in_secs;

  InitPlayer(&player);
  InitNextPlayer(&next_player);
  InitBoard(&board);
  InitGameStatus(&game_status);
  time_in_secs = GetTimeInMS();

  parameters.t_game_status_ = &game_status;
  parameters.t_state_ = &state;
  parameters.t_board_ = &board;
  parameters.t_player_ = &player;
  parameters.t_next_player_ = &next_player;
  parameters.t_predict_player_ = &predict_player;
  parameters.t_last_moved_time_ = &time_in_secs;
  parameters.t_records_ = &records;

  LoadRecords(parameters.t_records_, TETRIS_RECORDS_FILE_NAME);
  SaveRecords(parameters.t_records_, TETRIS_RECORDS_FILE_NAME);

  InitGameColors();
  PrintBegin();
  TetrisLoop(&parameters);
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
