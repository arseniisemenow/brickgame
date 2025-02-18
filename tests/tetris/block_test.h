#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_BLOCK_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_BLOCK_TEST_H_
#ifndef TEST_HEADER_
#define TEST_HEADER_

#include "../../src/brick_game/tetris/backend/backend.h"
#include "test.h"

#endif

START_TEST(GetRandomBlockTypeTest) {
  BlockType block_type = {};
  block_type = GetRandomBlockType();
  ck_assert_int_ge(block_type, 0);
}
END_TEST

START_TEST(GetNextBlockRotationTest) {
  Direction block_rotation = kDirectionFirst;
  block_rotation = GetNextBlockRotation(block_rotation);
  ck_assert_int_eq(block_rotation, kDirectionSecond);
  block_rotation = GetNextBlockRotation(block_rotation);
  ck_assert_int_eq(block_rotation, kDirectionThird);
  block_rotation = GetNextBlockRotation(block_rotation);
  ck_assert_int_eq(block_rotation, kDirectionForth);
}
END_TEST

START_TEST(GetPreviousBlockRotationTest) {
  Direction block_rotation = kDirectionFirst;
  block_rotation = GetPreviousBlockRotation(block_rotation);
  ck_assert_int_eq(block_rotation, kDirectionForth);
  block_rotation = GetPreviousBlockRotation(block_rotation);
  ck_assert_int_eq(block_rotation, kDirectionThird);
  block_rotation = GetPreviousBlockRotation(block_rotation);
  ck_assert_int_eq(block_rotation, kDirectionSecond);
  block_rotation = GetPreviousBlockRotation(block_rotation);
  ck_assert_int_eq(block_rotation, kDirectionFirst);
}
END_TEST

Suite *block_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("block suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, GetRandomBlockTypeTest);
  tcase_add_test(tc_core, GetNextBlockRotationTest);
  tcase_add_test(tc_core, GetPreviousBlockRotationTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_BLOCK_TEST_H_