#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../../src/brick_game/tetris/backend/backend.h"
#include "test.h"
#endif

void AssertPlayerBoardSettedCells(const Player *p_player,
                                  const Board *p_board) {
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (p_player->board_->board_[i][j].is_set_) {
        ck_assert_int_ge(
            p_board->cells_[p_player->y_ + i][p_player->x_ + j].is_set_, 0);
      }
    }
  }
}

START_TEST(BoardOverlayBlockTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitBoard(board);
  SetPlayerBlockType(player, kBlockO);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);

  AssertPlayerBoardSettedCells(player, board);
}
END_TEST

START_TEST(BoardOverlayBlockOnAnotherBlockTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitBoard(board);

  SetPlayerBlockType(player, kBlockO);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);

  SetPlayerBlockType(player, kBlockO);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);

  AssertPlayerBoardSettedCells(player, board);
}
END_TEST

START_TEST(UpdatePredictPlayerTest) {
  Player *player = AllocPlayer();
  Player *predict_player = AllocPlayer();
  Board *board = AllocBoard();

  InitBoard(board);
  InitPlayerPosition(player);
  SetPlayerBlockType(player, kBlockJ);
  UpdatePredictPlayer(predict_player, player, board);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ck_assert_int_eq(predict_player->x_, player->x_);
      ck_assert_int_ge(predict_player->y_, -1);
      ck_assert_int_ge(player->y_, -1);
    }
  }
}

END_TEST
START_TEST(GetTimeStepMSTest) {
  GameStatus *game_status = AllocGameStatus();
  game_status->level_ = 0;

  long long time_step_ms = GetTimeStepMS(game_status);
  ck_assert_int_eq(time_step_ms, 1000);
  game_status->level_ = 1;
  time_step_ms = GetTimeStepMS(game_status);
  ck_assert_int_eq(time_step_ms, 875);
  game_status->level_ = 2;
  time_step_ms = GetTimeStepMS(game_status);
  ck_assert_int_eq(time_step_ms, 625);
}

END_TEST

Suite *backend_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("backend suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, BoardOverlayBlockTest);
  tcase_add_test(tc_core, BoardOverlayBlockOnAnotherBlockTest);
  tcase_add_test(tc_core, UpdatePredictPlayerTest);
  tcase_add_test(tc_core, GetTimeStepMSTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif // C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_
