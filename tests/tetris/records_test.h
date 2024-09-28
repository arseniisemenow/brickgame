#ifndef C7_BRICK_GAME_V_1_0_1_TESTS_RECORDS_TEST_H_
#define C7_BRICK_GAME_V_1_0_1_TESTS_RECORDS_TEST_H_

#ifndef TEST_HEADER_
#define TEST_HEADER_
#include "../../src/brick_game/tetris/backend/backend.h"
#include "test.h"
#endif

START_TEST(RecordsAddSaveLoadTest1) {
    Records* records = AllocRecords();
    Records* records2 = AllocRecords();
    InitRecords(records);
    InitRecords(records2);

    AddRecord(records, "Arsenii1", 500, TETRIS_RECORDS_FILE_NAME);
    AddRecord(records, "Arsenii2", 600, TETRIS_RECORDS_FILE_NAME);
    AddRecord(records, "Arsenii3", 700, TETRIS_RECORDS_FILE_NAME);
    AddRecord(records, "Arsenii4", 800, TETRIS_RECORDS_FILE_NAME);
    AddRecord(records, "Arsenii5", 900, TETRIS_RECORDS_FILE_NAME);
    AddRecord(records, "Arsenii6", 1000, TETRIS_RECORDS_FILE_NAME);

    SaveRecords(records, TETRIS_RECORDS_FILE_NAME);
    LoadRecords(records2, TETRIS_RECORDS_FILE_NAME);
    for (int i = 0; i < RECORDS_NUMBER; ++i) {
      ck_assert_int_eq(records->records_[i].is_current_player_,
                       records2->records_[i].is_current_player_);
      ck_assert_int_eq(records->records_[i].score_, records2->records_[i].score_);
      ck_assert_str_eq(records->records_[i].name_, records2->records_[i].name_);
    }
}

END_TEST
START_TEST(RecordsAddSaveLoadTest2) {
  Records* records = AllocRecords();
  Records* records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 600, TETRIS_RECORDS_FILE_NAME);

  SaveRecords(records, TETRIS_RECORDS_FILE_NAME);
  LoadRecords(records2, TETRIS_RECORDS_FILE_NAME);
  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    ck_assert_int_eq(records->records_[i].is_current_player_,
                     records2->records_[i].is_current_player_);
    ck_assert_int_eq(records->records_[i].score_, records2->records_[i].score_);
    ck_assert_str_eq(records->records_[i].name_, records2->records_[i].name_);
  }
}

END_TEST
START_TEST(RecordsAddSaveLoadTest3) {
  Records* records = AllocRecords();
  Records* records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);
  const char * name = "Arsenii";
  const char * empty_name = "";
  const int first_score = 500;
  const int second_score = 600;
  const int empty_score = 0;


  ck_assert_str_eq(records->records_[0].name_, empty_name);
  ck_assert_str_eq(records->records_[1].name_, empty_name);
  ck_assert_str_eq(records->records_[2].name_, empty_name);
  ck_assert_str_eq(records->records_[3].name_, empty_name);
  ck_assert_str_eq(records->records_[4].name_, empty_name);
  ck_assert_int_eq(records->records_[0].score_, empty_score);
  ck_assert_int_eq(records->records_[1].score_, empty_score);
  ck_assert_int_eq(records->records_[2].score_, empty_score);
  ck_assert_int_eq(records->records_[3].score_, empty_score);
  ck_assert_int_eq(records->records_[4].score_, empty_score);

  AddRecord(records, name, first_score, TETRIS_RECORDS_FILE_NAME);
  ck_assert_str_eq(records->records_[0].name_, name);
  ck_assert_str_eq(records->records_[1].name_, empty_name);
  ck_assert_str_eq(records->records_[2].name_, empty_name);
  ck_assert_str_eq(records->records_[3].name_, empty_name);
  ck_assert_str_eq(records->records_[4].name_, empty_name);
  ck_assert_int_eq(records->records_[0].score_, first_score);
  ck_assert_int_eq(records->records_[1].score_, empty_score);
  ck_assert_int_eq(records->records_[2].score_, empty_score);
  ck_assert_int_eq(records->records_[3].score_, empty_score);
  ck_assert_int_eq(records->records_[4].score_, empty_score);

  AddRecord(records, name, second_score, TETRIS_RECORDS_FILE_NAME);

  ck_assert_str_eq(records->records_[0].name_, name);
  ck_assert_str_eq(records->records_[1].name_, empty_name);
  ck_assert_str_eq(records->records_[2].name_, empty_name);
  ck_assert_str_eq(records->records_[3].name_, empty_name);
  ck_assert_str_eq(records->records_[4].name_, empty_name);
  ck_assert_int_eq(records->records_[0].score_, second_score);
  ck_assert_int_eq(records->records_[1].score_, empty_score);
  ck_assert_int_eq(records->records_[2].score_, empty_score);
  ck_assert_int_eq(records->records_[3].score_, empty_score);
  ck_assert_int_eq(records->records_[4].score_, empty_score);
}

END_TEST

START_TEST(RecordsAddSaveLoadTest4) {
  Records* records = AllocRecords();
  Records* records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 600, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 600, TETRIS_RECORDS_FILE_NAME);
  RemoveRecord(records, "Arsenii", TETRIS_RECORDS_FILE_NAME);

  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    ck_assert_int_eq(records->records_[i].score_, 0);
    ck_assert_int_eq(records->records_[i].is_current_player_, false);
    ck_assert_str_eq(records->records_[i].name_, "");
  }
}

END_TEST

START_TEST(RecordsAddSaveLoadTest5) {
  Records* records = AllocRecords();
  Records* records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii8", 1200, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii7", 1100, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii6", 1000, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii5", 900, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii4", 800, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii3", 700, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii2", 600, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii1", 500, TETRIS_RECORDS_FILE_NAME);

  ck_assert_int_eq(records->records_[0].score_, 1200);
  ck_assert_str_eq(records->records_[0].name_, "Arsenii8");
}

END_TEST


START_TEST(RecordsAddSaveLoadTest6) {
  Records* records = AllocRecords();
  Records* records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);
  const char * first_name = "Arsenii";
  const char * second_name = "Andrew";
  const char * empty_name = "";
  const int first_score_first_player = 500;
  const int first_score_second_player = 600;
  const int second_score_first_player = 700;
  const int second_score_second_player = 800;
  const int empty_score = 0;

  ck_assert_str_eq(records->records_[0].name_, empty_name);
  ck_assert_str_eq(records->records_[1].name_, empty_name);
  ck_assert_str_eq(records->records_[2].name_, empty_name);
  ck_assert_str_eq(records->records_[3].name_, empty_name);
  ck_assert_str_eq(records->records_[4].name_, empty_name);
  ck_assert_int_eq(records->records_[0].score_, empty_score);
  ck_assert_int_eq(records->records_[1].score_, empty_score);
  ck_assert_int_eq(records->records_[2].score_, empty_score);
  ck_assert_int_eq(records->records_[3].score_, empty_score);
  ck_assert_int_eq(records->records_[4].score_, empty_score);

  AddRecord(records, first_name, first_score_first_player, TETRIS_RECORDS_FILE_NAME);
  ck_assert_str_eq(records->records_[0].name_, first_name);
  ck_assert_str_eq(records->records_[1].name_, empty_name);
  ck_assert_str_eq(records->records_[2].name_, empty_name);
  ck_assert_str_eq(records->records_[3].name_, empty_name);
  ck_assert_str_eq(records->records_[4].name_, empty_name);
  ck_assert_int_eq(records->records_[0].score_, first_score_first_player);
  ck_assert_int_eq(records->records_[1].score_, empty_score);
  ck_assert_int_eq(records->records_[2].score_, empty_score);
  ck_assert_int_eq(records->records_[3].score_, empty_score);
  ck_assert_int_eq(records->records_[4].score_, empty_score);

  AddRecord(records, second_name, first_score_second_player, TETRIS_RECORDS_FILE_NAME);

  ck_assert_str_eq(records->records_[0].name_, second_name);
  ck_assert_str_eq(records->records_[1].name_, first_name);
  ck_assert_str_eq(records->records_[2].name_, empty_name);
  ck_assert_str_eq(records->records_[3].name_, empty_name);
  ck_assert_str_eq(records->records_[4].name_, empty_name);
  ck_assert_int_eq(records->records_[0].score_, first_score_second_player);
  ck_assert_int_eq(records->records_[1].score_, first_score_first_player);
  ck_assert_int_eq(records->records_[2].score_, empty_score);
  ck_assert_int_eq(records->records_[3].score_, empty_score);
  ck_assert_int_eq(records->records_[4].score_, empty_score);

  AddRecord(records, first_name, second_score_first_player, TETRIS_RECORDS_FILE_NAME);

  ck_assert_str_eq(records->records_[0].name_, first_name);
  ck_assert_str_eq(records->records_[1].name_, second_name);
  ck_assert_str_eq(records->records_[2].name_, empty_name);
  ck_assert_str_eq(records->records_[3].name_, empty_name);
  ck_assert_str_eq(records->records_[4].name_, empty_name);
  ck_assert_int_eq(records->records_[0].score_, second_score_first_player);
  ck_assert_int_eq(records->records_[1].score_, first_score_second_player);
  ck_assert_int_eq(records->records_[2].score_, empty_score);
  ck_assert_int_eq(records->records_[3].score_, empty_score);
  ck_assert_int_eq(records->records_[4].score_, empty_score);

  AddRecord(records, second_name, second_score_second_player, TETRIS_RECORDS_FILE_NAME);

  ck_assert_str_eq(records->records_[0].name_, second_name);
  ck_assert_str_eq(records->records_[1].name_, first_name);
  ck_assert_str_eq(records->records_[2].name_, empty_name);
  ck_assert_str_eq(records->records_[3].name_, empty_name);
  ck_assert_str_eq(records->records_[4].name_, empty_name);
  ck_assert_int_eq(records->records_[0].score_, second_score_second_player);
  ck_assert_int_eq(records->records_[1].score_, second_score_first_player);
  ck_assert_int_eq(records->records_[2].score_, empty_score);
  ck_assert_int_eq(records->records_[3].score_, empty_score);
  ck_assert_int_eq(records->records_[4].score_, empty_score);
}

END_TEST

Suite *records_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("records suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, RecordsAddSaveLoadTest1);
  tcase_add_test(tc_core, RecordsAddSaveLoadTest2);
  tcase_add_test(tc_core, RecordsAddSaveLoadTest3);
  tcase_add_test(tc_core, RecordsAddSaveLoadTest4);
  tcase_add_test(tc_core, RecordsAddSaveLoadTest5);
  tcase_add_test(tc_core, RecordsAddSaveLoadTest6);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_RECORDS_TEST_H_