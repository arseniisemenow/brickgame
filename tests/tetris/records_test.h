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

START_TEST(RecordsAddSaveLoadTest4) {
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

Suite *records_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("records suite");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, RecordsAddSaveLoadTest1);
  tcase_add_test(tc_core, RecordsAddSaveLoadTest2);
  tcase_add_test(tc_core, RecordsAddSaveLoadTest3);
  tcase_add_test(tc_core, RecordsAddSaveLoadTest4);
  suite_add_tcase(s, tc_core);
  return s;
}

#endif  // C7_BRICK_GAME_V_1_0_1_TESTS_RECORDS_TEST_H_