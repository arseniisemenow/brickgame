#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_COLLISIONS_CHECKER_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_COLLISIONS_CHECKER_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../src/brick_game/tetris/backend/backend.h"
#include "test.h"
#endif

START_TEST(CheckCollideTest1) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);

  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  bool flag = CheckCollide(&player, &board);
  ck_assert_int_eq(flag, false);
}

END_TEST

START_TEST(CheckFutureCollideWithBlocksLeftTest1) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);

  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  bool flag = CheckFutureCollideWithBlocksLeft(&player, &board);
  ck_assert_int_eq(flag, false);
}

END_TEST

START_TEST(CheckFutureCollideWithBlocksRightTest1) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);
  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  bool flag = CheckFutureCollideWithBlocksRight(&player, &board);
  ck_assert_int_eq(flag, false);
}

END_TEST

START_TEST(CheckFutureCollideWithBlocksLeftTest2) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);
  for (int i = 0; i < board.height_; ++i) {
    board.cells_[i][0].is_set_ = true;
  }

  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);

  MovePlayerLeft(&player);
  MovePlayerLeft(&player);
  MovePlayerLeft(&player);
  bool flag = CheckFutureCollideWithBlocksLeft(&player, &board);
  ck_assert_int_eq(flag, true);
}

END_TEST
START_TEST(CheckFutureCollideWithBlocksRightTest2) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);
  for (int i = 0; i < board.height_; ++i) {
    board.cells_[i][board.width_ - 1].is_set_ = true;
  }

  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);

  MovePlayerRight(&player);
  MovePlayerRight(&player);
  bool flag = CheckFutureCollideWithBlocksRight(&player, &board);
  ck_assert_int_eq(flag, true);
}

END_TEST

START_TEST(CheckFutureCollideWithLeftTest) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);

  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  MovePlayerLeft(&player);
  MovePlayerLeft(&player);
  MovePlayerLeft(&player);
  MovePlayerLeft(&player);

  bool flag = CheckFutureCollideWithLeft(&player, &board);
  ck_assert_int_eq(flag, true);
}

END_TEST

START_TEST(CheckFutureCollideWithRightTest) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);

  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  MovePlayerRight(&player);
  MovePlayerRight(&player);
  MovePlayerRight(&player);

  bool flag = CheckFutureCollideWithRight(&player, &board);
  ck_assert_int_eq(flag, true);
}

END_TEST

START_TEST(CheckFutureCollideWithUpTest) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);

  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  MovePlayerRight(&player);
  MovePlayerRight(&player);
  MovePlayerRight(&player);

  bool flag = CheckFutureCollideWithUp(&player, &board);
  ck_assert_int_eq(flag, false);
}

END_TEST

START_TEST(CheckFutureCollideWithDownTest) {
  Player player = {0};
  Board board = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  InitBoard(&board);

  SetPlayerBlockType(&player, kBlockT);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  MovePlayerRight(&player);
  MovePlayerRight(&player);
  MovePlayerRight(&player);

  bool flag = CheckFutureCollideWithDown(&player, &board);
  ck_assert_int_eq(flag, false);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  flag = CheckFutureCollideWithDown(&player, &board);
  ck_assert_int_eq(flag, false);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  flag = CheckFutureCollideWithDown(&player, &board);
  ck_assert_int_eq(flag, false);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  flag = CheckFutureCollideWithDown(&player, &board);
  ck_assert_int_eq(flag, false);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  MovePlayerDown(&player);
  flag = CheckFutureCollideWithDown(&player, &board);
  ck_assert_int_eq(flag, true);
}

END_TEST

Suite *collisions_checker_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("collisions checker suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, CheckCollideTest1);
  tcase_add_test(tc_core, CheckFutureCollideWithBlocksLeftTest1);
  tcase_add_test(tc_core, CheckFutureCollideWithBlocksRightTest1);
  tcase_add_test(tc_core, CheckFutureCollideWithBlocksLeftTest2);
  tcase_add_test(tc_core, CheckFutureCollideWithBlocksRightTest2);
  tcase_add_test(tc_core, CheckFutureCollideWithLeftTest);
  tcase_add_test(tc_core, CheckFutureCollideWithRightTest);
  tcase_add_test(tc_core, CheckFutureCollideWithUpTest);
  tcase_add_test(tc_core, CheckFutureCollideWithDownTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_COLLISIONS_CHECKER_TEST_H_