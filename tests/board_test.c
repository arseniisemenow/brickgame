#include "board_test.h"

int main() {
  int errcode = 0;
  case_test(board_suite(), &errcode);
  return 0;
}