// #include "../../src/brick_game/tetris/backend/backend.h"
#include <assert.h>
#include <printf.h>

#include "../../src/brick_game/tetris/fsm/fsm.h"

#define TEST_TETRIS_RECORDS_FILE_NAME "test_tetris_records.log"

int main() {
  Records* records = AllocRecords();
  Records* records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii8", 1200, TEST_TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii7", 1100, TEST_TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii6", 1000, TEST_TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii5", 900, TEST_TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii4", 800, TEST_TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii3", 700, TEST_TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii2", 600, TEST_TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii1", 500, TEST_TETRIS_RECORDS_FILE_NAME);

  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    records->records_[0].is_current_player_, false;
  }
}