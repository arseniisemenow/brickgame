#include "player_board_test.h"

int main() {
  int errcode = 0;
  case_test(player_board_suite(), &errcode);
  return 0;
}