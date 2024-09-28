// #include "../../src/brick_game/tetris/backend/backend.h"
#include "../../src/brick_game/tetris/fsm/fsm.h"
#include <assert.h>
#include <printf.h>


int main() {
  Records* records = AllocRecords();
  Records* records2 = AllocRecords();
//  LoadRecords(records, "../../../"TETRIS_RECORDS_FILE_NAME);
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 600, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 600, TETRIS_RECORDS_FILE_NAME);
  RemoveRecord(records, "Arsenii", TETRIS_RECORDS_FILE_NAME);

  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    records->records_[i].score_==0;
    records->records_[i].is_current_player_==false;
    strcmp(records->records_[i].name_,"") == 0;
  }
}