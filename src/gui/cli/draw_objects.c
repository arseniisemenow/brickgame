#include "draw_objects.h"


void DrawCar(int y, int lane, int color) {

  lane *= 3;
  y += BOARDS_BEGIN + 1;
  lane += BOARDS_BEGIN + 1;
  attron(COLOR_PAIR(color));
  mvprintw(y, lane + 0, "%s", "####");
  attroff(COLOR_PAIR(color));

  attron(COLOR_PAIR(color));
  mvprintw(y - 1, lane + 1, "##");
  attroff(COLOR_PAIR(color));


  attron(COLOR_PAIR(color));
  mvprintw(y - 2, lane + 0, "%s", "####");
  attroff(COLOR_PAIR(color));


  attron(COLOR_PAIR(color));
  mvprintw(y - 3, lane + 1, "##");
  attroff(COLOR_PAIR(color));
}

const char* kStateLabels[] = {
    "kStart",
    "kSpawn",
    "kMoving",
    "kCollide",
    "kGameOver",
    "kExitState",
    "kPause"
};
void PrintState(const State state){
//  attron(COLOR_PAIR(color));

  mvprintw(22, 15, "%12s", kStateLabels[state]);
//  attroff(COLOR_PAIR(color));
}

void DrawCarRacingBoard(CarRacingParameters *p) {
  DrawCar(p->player_car_racing_.y_, p->player_car_racing_.lane_, RED_COLOR_PAIR_INDEX);

  for (int i = 0; i < 2; i++) {
    DrawCar(p->rival_cars_[i].y_, p->rival_cars_[i].lane_, ORANGE_COLOR_PAIR_INDEX);
  }

  refresh();
}

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

void PrintCarRacingOverlay(void) {
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

  for (; i < right_x; i++)
    MVADDCH(top_y, i, ACS_HLINE);
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i_2 = top_y + 1; i_2 < bottom_y; i_2++) {
    MVADDCH(i_2, left_x, ACS_VLINE);
    MVADDCH(i_2, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++)
    MVADDCH(bottom_y, i, ACS_HLINE);
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
void PrintCarRacingStatus(CarRacingParameters *p_parameters) {
  MVPRINTW(2, BOARD_WIDTH + 5, "%7d", p_parameters->score_);
  MVPRINTW(5, BOARD_WIDTH + 5, "%7d", p_parameters->level_);
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
  PrintState(*p_parameters->t_state_);
}

void PrintSnakeGame(Parameters *p_parameters) {
  ClearGame();
  PrintSnakeOverlay();
  PrintRecords(7, p_parameters->s_records_);
  PrintSnakeGameStatus(p_parameters->s_game_status_);
  PrintSnakeAndFruit(p_parameters);
  PrintState(*p_parameters->s_state_);
}

void PrintCarRacingGame(CarRacingParameters *p_parameters) {
  ClearGame();
  PrintCarRacingOverlay();
  Records *records = AllocRecords();
  strcpy(records->records_[0].name_, "Unnamed");
  records->records_[0].score_ = p_parameters->record_score_;
  PrintRecords(7, records);
  FreeRecords(records);
  DrawCarRacingBoard(p_parameters);
  PrintCarRacingStatus(p_parameters);
  PrintState((State)p_parameters->state_);
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
  const PlayerBoard *player_board = (const PlayerBoard *)p_player->board_;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      int print_y = player_pos_y + BOARDS_BEGIN + 1 + row_index;
      int print_x = player_pos_x + BOARDS_BEGIN + 1 + column_index;
      if (player_board->board_[row_index][column_index].is_set_) {
        int color = player_board->board_[row_index][column_index].color_;
        attron(COLOR_PAIR(kBlockColorPairsArray[color]));
        mvprintw(print_y, print_x, "F");
        attroff(COLOR_PAIR(kBlockColorPairsArray[color]));
      }
    }
  }
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
  PrintRectangle(shift, shift + 6, 13, 24);
  mvprintw(shift + 2, 16, "Records");

  const unsigned char kColorPair[5] = {
      RECORD_1_COLOR_PAIR_INDEX, RECORD_2_COLOR_PAIR_INDEX,
      RECORD_3_COLOR_PAIR_INDEX, RECORD_4_5_COLOR_PAIR_INDEX,
      RECORD_4_5_COLOR_PAIR_INDEX};

  for (int i = 0; i < NAME_LENGTH; ++i) {
    char name[NAME_LENGTH] = {0};
    strncpy(name, p_records->records_[i].name_, NAME_LENGTH - 1);
    for (int j = 0; j < NAME_LENGTH - 1; ++j) {
      if (!isalnum(name[i])) {
        name[j] = '?';
      }
    }
    attron(COLOR_PAIR(kColorPair[i]));
    mvprintw(shift + 3 + i, 16, "%d.%s %4d", i + 1, name,
             p_records->records_[i].score_);
    attroff(COLOR_PAIR(kColorPair[i]));
  }
  //
  //  attron(COLOR_PAIR(RECORD_1_COLOR_PAIR_INDEX));
  //  mvprintw(shift + 3, 16, "1. %s %4d", p_records->records_[0].name_,
  //  p_records->records_[0].score_);
  //  attron(COLOR_PAIR(RECORD_1_COLOR_PAIR_INDEX));
  //  attron(COLOR_PAIR(RECORD_2_COLOR_PAIR_INDEX));
  //  mvprintw(shift + 4, 16, "2. %7d", p_records->records_[1].score_);
  //  attroff(COLOR_PAIR(RECORD_2_COLOR_PAIR_INDEX));
  //  attron(COLOR_PAIR(RECORD_3_COLOR_PAIR_INDEX));
  //  mvprintw(shift + 5, 16, "3. %7d", p_records->records_[2].score_);
  //  attroff(COLOR_PAIR(RECORD_3_COLOR_PAIR_INDEX));
  //
  //  attron(COLOR_PAIR(RECORD_4_5_COLOR_PAIR_INDEX));
  //  mvprintw(shift + 6, 16, "4. %7d", p_records->records_[3].score_);
  //  attroff(COLOR_PAIR(RECORD_4_5_COLOR_PAIR_INDEX));
  //  attron(COLOR_PAIR(RECORD_4_5_COLOR_PAIR_INDEX));
  //  mvprintw(shift + 7, 16, "5. %7d", p_records->records_[4].score_);
  //  attroff(COLOR_PAIR(RECORD_4_5_COLOR_PAIR_INDEX));
}
