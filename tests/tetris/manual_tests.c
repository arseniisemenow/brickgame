// #include "../../src/brick_game/tetris/backend/backend.h"
#include "../../src/brick_game/tetris/fsm/fsm.h"
#include <assert.h>
#include <printf.h>


int main() {
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

  AddRecord(records, first_name, first_score_first_player, TETRIS_RECORDS_FILE_NAME);

  AddRecord(records, second_name, first_score_second_player, TETRIS_RECORDS_FILE_NAME);

  AddRecord(records, first_name, second_score_first_player, TETRIS_RECORDS_FILE_NAME);

  AddRecord(records, second_name, second_score_second_player, TETRIS_RECORDS_FILE_NAME);

}