#ifndef CPP3_BRICK_GAME_V_2_0_1_GUI_CLI_FRONTEND_H_
#define CPP3_BRICK_GAME_V_2_0_1_GUI_CLI_FRONTEND_H_

#include "../../brick_game/common/block/block.h"
#include "../../brick_game/common/board/board.h"
#include "../../brick_game/common/cell/cell.h"
#include "../../brick_game/common/common/color_handler.h"
#include "../../brick_game/common/game_status/game_status.h"
#include "../../brick_game/common/parameters/parameters.h"
#include "../../brick_game/common/player/player.h"
#include "../../brick_game/common/time_handler/time_handler.h"

#define WIN_INIT(time)     \
  {                        \
    initscr();             \
    noecho();              \
    curs_set(0);           \
    keypad(stdscr, TRUE);  \
    timeout(time);         \
    nodelay(stdscr, TRUE); \
    start_color();         \
  }

#define GET_USER_INPUT getch()

#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#define MAX_LENGTH_NAME (10)

typedef enum {
  kGameStateNone = 0,
  kGameStateStart = 1,
  kGameStateTetris = 2,
  kGameStateSnake = 3,
  kGameStateCarRacing = 4,
  kGameStateTankClassic = 5,
  kGameStateExit = 6,
} GameState;

void PrintUserNamePrompt();
void PrintTetrisOverlay(void);
void PrintSnakeOverlay(void);

void PrintSnakeGameStatus(GameStatus *p_game_status);

void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x);
void PrintTetrisGameStatus(GameStatus *p_game_status);
void PrintTetrisGame(Parameters *p_parameters);
void PrintSnakeGame(Parameters *p_parameters);
void PrintSnakeAndFruit(Parameters *p_parameters);
void ClearGame();
void PrintBlock(Player *p_player);
void PrintBoard(Board *p_board);
void GetPlayerName(char p_parameters[]);
void PrintBegin();
void PrintPause();
void ClearRecords();
void PrintRecords(int shift, Records *p_records);

void HandleTetrisLoop();
void SnakeLoop();

int CreateMenu(const char *options[], int size);

#endif  // CPP3_BRICK_GAME_V_2_0_1_GUI_CLI_FRONTEND_H_