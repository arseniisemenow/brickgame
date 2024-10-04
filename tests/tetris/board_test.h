#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_BOARD_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_BOARD_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../../src/brick_game/tetris/backend/backend.h"
#include "test.h"
#endif

START_TEST(HandleBoardCompleteLinesTest) {
  Board *board = AllocBoard();
  InitBoard(board);

  for (int i = 0; i < board->width_; ++i) {
    board->cells_[19][i].is_set_ = true;
  }
  for (int i = 0; i < board->width_; ++i) {
    board->cells_[18][i].is_set_ = true;
  }
  for (int i = 0; i < board->width_; i++) {
    board->cells_[17][i].is_set_ = true;
  }
  for (int i = 0; i < board->width_; i += 2) {
    board->cells_[16][i].is_set_ = true;
  }
  int complete_lines = HandleBoardCompleteLines(board);
  ck_assert_int_eq(complete_lines, 3);
  FreeBoard(board);
}
END_TEST

Suite *board_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("board suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, HandleBoardCompleteLinesTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_BOARD_TEST_H_
