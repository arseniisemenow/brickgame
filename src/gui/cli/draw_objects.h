#ifndef BRICKGAME_DESKTOP_SRC_GUI_CLI_DRAW_OBJECTS_H_
#define BRICKGAME_DESKTOP_SRC_GUI_CLI_DRAW_OBJECTS_H_

#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "../../brick_game/common/api_client/api_client.h"
#include "../../brick_game/snake/controller/controller.h"
#include "../../brick_game/tetris/fsm/fsm.h"

#define NAME_LENGTH (4)

void DrawCar(int y, int lane, int color);
void PrintState(const State state);

// Function to draw the game board based on car racing parameters
void DrawCarRacingBoard(CarRacingParameters *car_racing_parameters);

void PrintTetrisOverlay(void);
void PrintSnakeOverlay(void);
void PrintCarRacingOverlay(void);

void PrintUserNamePrompt();

void PrintRectangle(int top_y, int bottom_y, int left_x, int right_x);

void PrintTetrisGameStatus(GameStatus *p_game_status);
void PrintSnakeGameStatus(GameStatus *p_game_status);
void PrintCarRacingStatus(CarRacingParameters *p_parameters);
void ClearGame();

void PrintTetrisGame(Parameters *p_parameters);

void PrintSnakeGame(Parameters *p_parameters);
void PrintCarRacingGame(CarRacingParameters *p_parameters);

void PrintSnakeAndFruit(Parameters *p_parameters);

void PrintBoard(Board *p_board);

void PrintBlock(Player *p_player);

void PrintBegin();

void PrintPause();

void ClearRecords();

void PrintRecords(int shift, Records *p_records);

#endif  // BRICKGAME_DESKTOP_SRC_GUI_CLI_DRAW_OBJECTS_H_
