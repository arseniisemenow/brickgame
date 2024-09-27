#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_PLAYER_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_PLAYER_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../src/brick_game/tetris/backend/backend.h"
#include "test.h"
#endif

START_TEST(InitPlayerTest) {
  Player player = {0};
  InitPlayer(&player);
  ck_assert_int_eq(player.x_, 0);
  ck_assert_int_eq(player.y_, 0);
  ck_assert_int_ge(player.block_type_, 0);
  ck_assert_int_ge(player.block_rotation_, 0);
}
END_TEST
START_TEST(InitNextPlayerTest) {
  Player player = {0};
  InitNextPlayer(&player);
  ck_assert_int_eq(player.x_, INIT_NEXT_PLAYER_POS_X);
  ck_assert_int_eq(player.y_, INIT_NEXT_PLAYER_POS_Y);
  ck_assert_int_ge(player.block_type_, 0);
  ck_assert_int_ge(player.block_rotation_, 0);
}
END_TEST
START_TEST(InitPlayerPositionTest) {
  Player player = {0};
  InitPlayerPosition(&player);
  ck_assert_int_eq(player.x_, INIT_PLAYER_POS_X);
  ck_assert_int_eq(player.y_, INIT_PLAYER_POS_Y);
  ck_assert_int_ge(player.block_type_, 0);
  ck_assert_int_ge(player.block_rotation_, 0);
}
START_TEST(CopyPlayerTest) {
  Player player = {0};
  InitNextPlayer(&player);
  Player player_2 = {0};
  CopyPlayer(&player_2, player);

  ck_assert_int_eq(player_2.x_, player.x_);
  ck_assert_int_eq(player_2.y_, player.y_);
  ck_assert_int_eq(player_2.block_type_, player.block_type_);
  ck_assert_int_eq(player_2.block_rotation_, player.block_rotation_);
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ck_assert_int_eq(player.board_.board_[i][j].color_,
                       player.board_.board_[i][j].color_);
      ck_assert_int_eq(player.board_.board_[i][j].is_set_,
                       player.board_.board_[i][j].is_set_);
    }
  }
}
END_TEST
START_TEST(SetPlayerBlockRotationTest) {
  Player player = {0};
  InitPlayer(&player);
  SetPlayerBlockRotation(&player, kBlockRotationThird);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationThird);
}
END_TEST
START_TEST(SetPlayerNextBlockRotationTest) {
  Player player = {0};
  InitPlayer(&player);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  SetPlayerNextBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationSecond);
  SetPlayerNextBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationThird);
  SetPlayerNextBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationForth);
  SetPlayerNextBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationFirst);
}
END_TEST
START_TEST(SetPlayerPreviousBlockRotationTest) {
  Player player = {0};
  InitPlayer(&player);
  SetPlayerBlockRotation(&player, kBlockRotationFirst);
  SetPlayerPreviousBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationForth);
  SetPlayerPreviousBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationThird);
  SetPlayerPreviousBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationSecond);
  SetPlayerPreviousBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationFirst);
  SetPlayerPreviousBlockRotation(&player);
  ck_assert_int_eq(player.block_rotation_, kBlockRotationForth);
}
END_TEST
START_TEST(MovePlayerRightTest1) {
  Player player = {0};
  Player player_before = {0};
  InitPlayer(&player);
  InitPlayer(&player_before);
  InitPlayerPosition(&player);
  InitPlayerPosition(&player_before);

  MovePlayerRight(&player);

  ck_assert_int_eq(player.x_, player_before.x_ + 1);
  ck_assert_int_eq(player.y_, player_before.y_);
}
END_TEST
START_TEST(MovePlayerRightTest2) {
  Player player = {0};
  Player player_before = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);
  CopyPlayer(&player_before, player);

  MovePlayerRight(&player);
  MovePlayerRight(&player);
  MovePlayerRight(&player);
  ck_assert_int_eq(player.x_, player_before.x_ + 3);
  ck_assert_int_eq(player.y_, player_before.y_);
}
END_TEST
START_TEST(MovePlayerLeftRightTest) {
  Player player = {0};
  Player player_before = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);

  CopyPlayer(&player_before, player);

  MovePlayerRight(&player);
  MovePlayerLeft(&player);

  ck_assert_int_eq(player_before.x_, player.x_);
  ck_assert_int_eq(player_before.y_, player.y_);
  ck_assert_int_eq(player_before.block_type_, player.block_type_);
  ck_assert_int_eq(player_before.block_rotation_, player.block_rotation_);
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ck_assert_int_eq(player.board_.board_[i][j].color_,
                       player_before.board_.board_[i][j].color_);
      ck_assert_int_eq(player.board_.board_[i][j].is_set_,
                       player_before.board_.board_[i][j].is_set_);
    }
  }
}
END_TEST

START_TEST(MovePlayerUpTest) {
  Player player = {0};
  Player player_before = {0};
  InitPlayer(&player);
  InitPlayer(&player_before);
  CopyPlayer(&player_before, player);

  MovePlayerUp(&player);

  ck_assert_int_eq(player_before.x_, player.x_);
  ck_assert_int_eq(player_before.y_, player.y_ + 1);
  ck_assert_int_eq(player_before.block_type_, player.block_type_);
  ck_assert_int_eq(player_before.block_rotation_, player.block_rotation_);
}
END_TEST

START_TEST(MovePlayerUpDownTest) {
  Player player = {0};
  Player player_before = {0};
  InitPlayer(&player);
  InitPlayerPosition(&player);
  CopyPlayer(&player_before, player);

  MovePlayerUp(&player);
  MovePlayerDown(&player);

  ck_assert_int_eq(player_before.x_, player.x_);
  ck_assert_int_eq(player_before.y_, player.y_);
  ck_assert_int_eq(player_before.block_type_, player.block_type_);
  ck_assert_int_eq(player_before.block_rotation_, player.block_rotation_);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ck_assert_int_eq(player.board_.board_[i][j].color_,
                       player_before.board_.board_[i][j].color_);
      ck_assert_int_eq(player.board_.board_[i][j].is_set_,
                       player_before.board_.board_[i][j].is_set_);
    }
  }
}
END_TEST

Suite *player_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("player suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, InitPlayerTest);
  tcase_add_test(tc_core, InitNextPlayerTest);
  tcase_add_test(tc_core, InitPlayerPositionTest);
  tcase_add_test(tc_core, CopyPlayerTest);
  tcase_add_test(tc_core, SetPlayerBlockRotationTest);
  tcase_add_test(tc_core, SetPlayerNextBlockRotationTest);
  tcase_add_test(tc_core, SetPlayerPreviousBlockRotationTest);
  tcase_add_test(tc_core, MovePlayerRightTest1);
  tcase_add_test(tc_core, MovePlayerRightTest2);
  tcase_add_test(tc_core, MovePlayerLeftRightTest);
  tcase_add_test(tc_core, MovePlayerUpTest);
  tcase_add_test(tc_core, MovePlayerUpDownTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_PLAYER_TEST_H_
