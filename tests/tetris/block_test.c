#include "block_test.h"

int main() {
  int errcode = 0;
  case_test(block_suite(), &errcode);
  return 0;
}