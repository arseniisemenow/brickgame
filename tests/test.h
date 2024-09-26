#ifndef C7_BRICKGAME_V1_0_1_TESTS_TEST_H_
#define C7_BRICKGAME_V1_0_1_TESTS_TEST_H_

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CASE_TEST
#define CASE_TEST

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  enum fork_status fork_status = CK_NOFORK;
  srunner_set_fork_status(runner, fork_status);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

#endif

#endif