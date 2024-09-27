#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_GAME_STATUS_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_GAME_STATUS_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../../src/brick_game/tetris/backend/backend.h"
#include "test.h"
#endif

START_TEST(InitGameStatusTest) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);
}

END_TEST
START_TEST(AddScoreGameStatusTest1) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);

  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 100);
  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 200);
  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 300);
  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 400);
  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 500);
}

END_TEST
START_TEST(AddScoreGameStatusTest2) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);

  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 100);
  AddScoreGameStatus(game_status, 2);
  ck_assert_int_eq(game_status->score_, 400);
  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 500);
  AddScoreGameStatus(game_status, 2);
  ck_assert_int_eq(game_status->score_, 800);
  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 900);
}

END_TEST
START_TEST(AddScoreGameStatusTest3) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);

  AddScoreGameStatus(game_status, 1);
  ck_assert_int_eq(game_status->score_, 100);
  AddScoreGameStatus(game_status, 2);
  ck_assert_int_eq(game_status->score_, 400);
  AddScoreGameStatus(game_status, 3);
  ck_assert_int_eq(game_status->score_, 1100);
  AddScoreGameStatus(game_status, 4);
  ck_assert_int_eq(game_status->score_, 2600);
  AddScoreGameStatus(game_status, 5);
  ck_assert_int_eq(game_status->score_, 4100);
}

END_TEST
START_TEST(AddScoreGameStatusUpdateGameStatusLevelTest1) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);

  AddScoreGameStatus(game_status, 1);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 100);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, 2);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 400);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, 1);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 500);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, 2);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 800);
  ck_assert_int_eq(game_status->level_, 1);
  AddScoreGameStatus(game_status, 1);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 900);
  ck_assert_int_eq(game_status->level_, 1);
}

END_TEST
START_TEST(AddScoreGameStatusUpdateGameStatusLevelTest2) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);

  AddScoreGameStatus(game_status, 1);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 100);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, 2);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 400);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, 3);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 1100);
  ck_assert_int_eq(game_status->level_, 1);
  AddScoreGameStatus(game_status, 4);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 2600);
  ck_assert_int_eq(game_status->level_, 4);
  AddScoreGameStatus(game_status, 5);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 4100);
  ck_assert_int_eq(game_status->level_, 6);
}

END_TEST
START_TEST(AddScoreGameStatusNoChangesTest) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);

  AddScoreGameStatus(game_status, 0);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, 0);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, 0);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, 0);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);
}

END_TEST
START_TEST(AddScoreGameStatusInvalidArgumentTest) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);

  AddScoreGameStatus(game_status, -1);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);
  AddScoreGameStatus(game_status, -100);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);
}

END_TEST

START_TEST(AddScoreGameStatusUpdateGameStatusLevelMaxLevelExceedTest) {
  GameStatus *game_status = AllocGameStatus();
  InitGameStatus(game_status);
  ck_assert_int_eq(game_status->score_, 0);
  ck_assert_int_eq(game_status->level_, 0);

  AddScoreGameStatus(game_status, 4);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 1500);
  ck_assert_int_eq(game_status->level_, 2);

  AddScoreGameStatus(game_status, 4);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 3000);
  ck_assert_int_eq(game_status->level_, 5);

  AddScoreGameStatus(game_status, 4);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 4500);
  ck_assert_int_eq(game_status->level_, 7);

  AddScoreGameStatus(game_status, 4);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 6000);
  ck_assert_int_eq(game_status->level_, 10);

  AddScoreGameStatus(game_status, 4);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 7500);
  ck_assert_int_eq(game_status->level_, 10);

  AddScoreGameStatus(game_status, 4);
  UpdateGameStatusLevel(game_status);
  ck_assert_int_eq(game_status->score_, 9000);
  ck_assert_int_eq(game_status->level_, 10);
}

Suite *game_status_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("game status suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, InitGameStatusTest);
  tcase_add_test(tc_core, AddScoreGameStatusTest1);
  tcase_add_test(tc_core, AddScoreGameStatusTest2);
  tcase_add_test(tc_core, AddScoreGameStatusTest3);
  tcase_add_test(tc_core, AddScoreGameStatusUpdateGameStatusLevelTest1);
  tcase_add_test(tc_core, AddScoreGameStatusUpdateGameStatusLevelTest2);
  tcase_add_test(tc_core, AddScoreGameStatusNoChangesTest);
  tcase_add_test(tc_core, AddScoreGameStatusInvalidArgumentTest);
  tcase_add_test(tc_core,
                 AddScoreGameStatusUpdateGameStatusLevelMaxLevelExceedTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_GAME_STATUS_TEST_H_