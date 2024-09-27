#include "game_status_test.h"

int main() {
  int errcode = 0;
  case_test(game_status_suite(), &errcode);
  return 0;
}