#include "frontend.h"

#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <ctime> // For Fedora

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
