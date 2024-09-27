#include "records_test.h"

int main() {
  int errcode = 0;
  case_test(records_suite(), &errcode);
  return 0;
}