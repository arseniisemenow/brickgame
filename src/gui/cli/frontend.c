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

#include "cJSON.h"
#include <curl/curl.h>

#define SERVER "127.0.0.1" // Replace with your server IP
#define PORT 8080
#define BUFFER_SIZE 4096
// Function to draw a car on the game board
void DrawCar(int y, int lane, int color) {
  lane *= 3; // Adjust lane spacing
  attron(COLOR_PAIR(color));

  mvprintw(y, lane, "####");
  mvprintw(y - 1, lane, " ## ");
  mvprintw(y - 2, lane, "####");
  mvprintw(y - 3, lane, " ## ");

  attroff(COLOR_PAIR(color));
}

// Function to draw the game board based on car racing parameters
void DrawCarRacingBoard(cJSON *car_racing_parameters) {
  cJSON *player_car_racing =
      cJSON_GetObjectItem(car_racing_parameters, "player_car_racing");
  cJSON *rival_cars = cJSON_GetObjectItem(car_racing_parameters, "rival_cars");
  int track_height =
      cJSON_GetObjectItem(car_racing_parameters, "track_height")->valueint;
  int track_width =
      cJSON_GetObjectItem(car_racing_parameters, "track_width")->valueint;

  clear();

  // Draw the track
  for (int i = 0; i < track_height; i++) {
    mvprintw(i, 0, "|");
    for (int j = 1; j < track_width * 3; j++) {
      printw(" ");
    }
    printw("|");
  }

  // Draw player car
  int player_lane = cJSON_GetObjectItem(player_car_racing, "lane")->valueint;
  int player_y = cJSON_GetObjectItem(player_car_racing, "y")->valueint;
  DrawCar(player_y, player_lane, 1); // Using color pair 1 for player car

  // Draw rival cars
  for (int i = 0; i < cJSON_GetArraySize(rival_cars); i++) {
    cJSON *rival_car = cJSON_GetArrayItem(rival_cars, i);
    int rival_lane = cJSON_GetObjectItem(rival_car, "lane")->valueint;
    int rival_y = cJSON_GetObjectItem(rival_car, "y")->valueint;
    DrawCar(rival_y, rival_lane, 2); // Using color pair 2 for rival cars
  }

  refresh();
}

// Struct to hold the response data from the server
struct MemoryStruct {
  char *memory;
  size_t size;
};

// Callback function for handling data received by cURL
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
                                  void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
    printf("Not enough memory to allocate\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

int MakeAction(const int action) {
  CURL *curl;
  CURLcode res;
  int success = 0;

  // Initialize cURL
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    // Prepare the URL and data to send
    const char *url = "http://127.0.0.1:8080/api/actions";
    char json_data[256];
    snprintf(json_data, sizeof(json_data), "{\"action\": \"%d\"}", action);

    // Set the URL
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Set the request type to POST
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // Set the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

    // Set the content type to JSON
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Perform the POST request
    res = curl_easy_perform(curl);

    // Check if the request was successful
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    } else {
      printf("Action \"%s\" sent successfully.\n", action);
      success = 1;
    }

    // Clean up
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  // Clean up cURL globally
  curl_global_cleanup();

  return success;
}

cJSON *GetGameStateFromServer() {
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;

  // Initialize the response memory
  chunk.memory = (char *)malloc(1);
  chunk.size = 0;

  // Initialize cURL
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    // Set the URL for the request
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8080/api/parameters");

    // Set the write callback function to handle data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    // Pass the chunk struct to the callback function
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    // Clean up cURL
    curl_easy_cleanup(curl);
  }

  // Parse the received JSON data
  cJSON *game_state = cJSON_Parse(chunk.memory);
  if (game_state == NULL) {
    printf("Error parsing JSON\n");
  }

  // Free the chunk memory
  free(chunk.memory);

  // Clean up cURL global environment
  curl_global_cleanup();

  return game_state;
}

void SendAction(char *action) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/api/actions");

    // Set the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
                     action); // Example: "{\"action\": \"move_left\"}"

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    // Cleanup
    curl_easy_cleanup(curl);
  }
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

#define NAME_LENGTH (4)

void PrintRecords(int shift, Records *p_records) {
  ClearRecords();
  PrintRectangle(shift, 20, 13, 24);
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
    mvprintw(shift + 3 + i, 16, "%d. %s %4d", i + 1, name,
             p_records->records_[i].score_);
    attron(COLOR_PAIR(kColorPair[i]));
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
