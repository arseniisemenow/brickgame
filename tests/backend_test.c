#include "backend_test.h"

int main() {
  int errcode = 0;
  case_test(backend_suite(), &errcode);
  return 0;
}