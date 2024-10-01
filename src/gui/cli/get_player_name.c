#include "get_player_name.h"

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