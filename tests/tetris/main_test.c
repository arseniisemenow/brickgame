#include "main_test.h"

int main() {
  int errcode = 0;
  case_test(block_suite(), &errcode);
  case_test(player_board_suite(), &errcode);
  case_test(board_suite(), &errcode);
  case_test(records_suite(), &errcode);
  case_test(player_suite(), &errcode);
  case_test(game_status_suite(), &errcode);
  case_test(collisions_checker_suite(), &errcode);
  case_test(backend_suite(), &errcode);
  return errcode;
}