#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_PLAYER_BOARD_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_PLAYER_BOARD_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../../src/brick_game/tetris/backend/backend.h"
#include "test.h"
#endif



START_TEST(SetPlayerBoardBlockTestIFirstRotation) {
  PlayerBoard *player_board = AllocPlayerBoard();
  SetPlayerBoardBlock(player_board, kBlockI, kDirectionFirst);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (j == 1) {
        ck_assert_int_eq(player_board->board_[i][j].is_set_, true);
      } else {
        ck_assert_int_eq(player_board->board_[i][j].is_set_, false);
      }
    }
  }
}
END_TEST

START_TEST(SetPlayerBoardBlockTestISecondRotation) {
  PlayerBoard *player_board = AllocPlayerBoard();
  SetPlayerBoardBlock(player_board, kBlockI, kDirectionSecond);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (i == 2) {
        ck_assert_int_eq(player_board->board_[i][j].is_set_, true);
      } else {
        ck_assert_int_eq(player_board->board_[i][j].is_set_, false);
      }
    }
  }
}
END_TEST

START_TEST(SetPlayerBoardBlockTestThirdRotation) {
  PlayerBoard *player_board = AllocPlayerBoard();
  SetPlayerBoardBlock(player_board, kBlockI, kDirectionThird);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (j == 1) {
        ck_assert_int_eq(player_board->board_[i][j].is_set_, true);
      } else {
        ck_assert_int_eq(player_board->board_[i][j].is_set_, false);
      }
    }
  }
}

END_TEST

START_TEST(SetPlayerBoardBlockTestIForthRotation) {
  PlayerBoard *player_board = AllocPlayerBoard();
  SetPlayerBoardBlock(player_board, kBlockI, kDirectionForth);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (i == 2) {
        ck_assert_int_eq(player_board->board_[i][j].is_set_, true);
      } else {
        ck_assert_int_eq(player_board->board_[i][j].is_set_, false);
      }
    }
  }
}
END_TEST

START_TEST(InitPlayerBoardTest) {
  PlayerBoard *player_board = AllocPlayerBoard();
  InitPlayerBoard(player_board);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ck_assert_int_eq(player_board->board_[i][j].color_, COLOR_BLACK);
      ck_assert_int_eq(player_board->board_[i][j].is_set_, false);
    }
  }
}
END_TEST

START_TEST(CopyPlayerBoardTest) {
  PlayerBoard *player_board_1 = AllocPlayerBoard();
  PlayerBoard *player_board_2 = AllocPlayerBoard();
  InitPlayerBoard(player_board_1);
  InitPlayerBoard(player_board_2);

  for (int i = 0; i < PLAYER_BOARD_SIZE; i += 2) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; j += 2) {
      player_board_1->board_[i][j].is_set_ = true;
    }
  }
  CopyPlayerBoard(player_board_2, player_board_1);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ck_assert_int_eq(player_board_1->board_[i][j].is_set_,
                       player_board_2->board_[i][j].is_set_);
      ck_assert_int_eq(player_board_1->board_[i][j].color_,
                       player_board_2->board_[i][j].color_);
    }
  }
}
END_TEST

Suite *player_board_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("player board suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, SetPlayerBoardBlockTestIFirstRotation);
  tcase_add_test(tc_core, SetPlayerBoardBlockTestISecondRotation);
  tcase_add_test(tc_core, SetPlayerBoardBlockTestThirdRotation);
  tcase_add_test(tc_core, SetPlayerBoardBlockTestIForthRotation);
  tcase_add_test(tc_core, InitPlayerBoardTest);
  tcase_add_test(tc_core, CopyPlayerBoardTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_PLAYER_BOARD_TEST_H_
