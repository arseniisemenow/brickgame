#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../src/brick_game/tetris/fsm/fsm.h"
#include "test.h"
#endif

START_TEST(ParamtersTest) {
  Parameters *p_params = AllocParameters();
  InitBoard(p_params->t_board_);
  SetPlayerBlockType(p_params->t_player_, kBlockO);
  InitPlayerPosition(p_params->t_player_);

  SignalType signal = kSignalNone;
//  SignalAction(signal, p_params);
//  BoardOverlayBlock(p_params->t_player_, p_params->t_board_);
  HandleBoardCompleteLines(p_params->t_board_);
}

END_TEST

Suite *backend_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("Parameters suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, ParamtersTest);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_BACKEND_TEST_H_
