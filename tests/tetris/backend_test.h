#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../../src/brick_game/tetris/fsm/fsm.h"
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
  SetPlayerBoardBlock(player->board_, kBlockO, kDirectionFirst);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);

  AssertPlayerBoardSettedCells(player, board);

  FreeBoard(board);
  FreePlayer(player);
}
END_TEST

START_TEST(BoardOverlayBlockOnAnotherBlockTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitBoard(board);

  SetPlayerBlockType(player, kBlockO);
  SetPlayerBoardBlock(player->board_, kBlockO, kDirectionFirst);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);

  SetPlayerBlockType(player, kBlockO);
  SetPlayerBoardBlock(player->board_, kBlockO, kDirectionFirst);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);

  AssertPlayerBoardSettedCells(player, board);
  FreeBoard(board);
  FreePlayer(player);
}
END_TEST

START_TEST(UpdatePredictPlayerTest) {
  Player *player = AllocPlayer();
  Player *predict_player = AllocPlayer();
  Board *board = AllocBoard();

  InitBoard(board);
  InitPlayerPosition(player);
  SetPlayerBlockType(player, kBlockJ);
  SetPlayerBoardBlock(player->board_, kBlockJ, kDirectionFirst);
  UpdatePredictPlayer(predict_player, player, board);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ck_assert_int_eq(predict_player->x_, player->x_);
      ck_assert_int_ge(predict_player->y_, -1);
      ck_assert_int_ge(player->y_, -1);
    }
  }
  FreeBoard(board);
  FreePlayer(player);
  FreePlayer(predict_player);
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
  FreeGameStatus(game_status);
}
END_TEST

void RepeatSignal(SignalType signal, Parameters *p_parameters, int times) {
  for (int i = 0; i < times; ++i) {
    SignalAction(signal, p_parameters);
  }
}

void PrintBoard(Parameters *p_parameters) {
  for (int i = 0; i < p_parameters->t_board_->height_; ++i) {
    for (int j = 0; j < p_parameters->t_board_->width_; ++j) {
      fprintf(stderr, "%d", p_parameters->t_board_->cells_[i][j].is_set_);
    }
    fprintf(stderr, "\n");
  }
}

START_TEST(FillFirstLineUsingSquaresTest) {
  Parameters *p_parameters = AllocParameters();

  InitPlayer(p_parameters->t_player_);
  InitNextPlayer(p_parameters->t_next_player_);
  InitBoard(p_parameters->t_board_);
  InitGameStatus(p_parameters->t_game_status_);

  *p_parameters->t_last_moved_time_ = GetTimeInMS();

  LoadRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);
  SaveRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);

  SignalAction(kSignalEnterButton, p_parameters);

  SetPlayerBlockType(p_parameters->t_player_, kBlockO);
  SetPlayerBoardBlock(p_parameters->t_player_->board_, kBlockO,
                      kDirectionFirst);
  RepeatSignal(kSignalMoveLeft, p_parameters, 10);
  RepeatSignal(kSignalMoveDown, p_parameters, 20);
  //    PrintBoard(p_parameters);

  SetPlayerBlockType(p_parameters->t_player_, kBlockO);
  SetPlayerBoardBlock(p_parameters->t_player_->board_, kBlockO,
                      kDirectionFirst);
  RepeatSignal(kSignalMoveLeft, p_parameters, 10);
  RepeatSignal(kSignalMoveRight, p_parameters, 2);
  RepeatSignal(kSignalMoveDown, p_parameters, 20);
  //    PrintBoard(p_parameters);
  SetPlayerBlockType(p_parameters->t_player_, kBlockO);
  SetPlayerBoardBlock(p_parameters->t_player_->board_, kBlockO,
                      kDirectionFirst);
  RepeatSignal(kSignalMoveLeft, p_parameters, 10);
  RepeatSignal(kSignalMoveRight, p_parameters, 4);
  RepeatSignal(kSignalMoveDown, p_parameters, 20);
  //    PrintBoard(p_parameters);
  SetPlayerBlockType(p_parameters->t_player_, kBlockO);
  SetPlayerBoardBlock(p_parameters->t_player_->board_, kBlockO,
                      kDirectionFirst);
  RepeatSignal(kSignalMoveLeft, p_parameters, 10);
  RepeatSignal(kSignalMoveRight, p_parameters, 6);
  RepeatSignal(kSignalMoveDown, p_parameters, 20);
  //    PrintBoard(p_parameters);
  SetPlayerBlockType(p_parameters->t_player_, kBlockO);
  SetPlayerBoardBlock(p_parameters->t_player_->board_, kBlockO,
                      kDirectionFirst);
  RepeatSignal(kSignalMoveLeft, p_parameters, 10);
  RepeatSignal(kSignalMoveRight, p_parameters, 8);
  RepeatSignal(kSignalMoveDown, p_parameters, 20);
  ck_assert_int_eq(p_parameters->t_game_status_->score_, 300);
  //    PrintBoard(p_parameters);

  FreeParameters(p_parameters);
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
  tcase_add_test(tc_core, FillFirstLineUsingSquaresTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_
