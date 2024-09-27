#include "collisions_checker_test.h"

int main() {
  int errcode = 0;
  case_test(collisions_checker_suite(), &errcode);
  return 0;
}