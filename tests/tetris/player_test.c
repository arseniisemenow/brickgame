#include "player_test.h"

int main() {
  int errcode = 0;
  case_test(player_suite(), &errcode);
  return 0;
}