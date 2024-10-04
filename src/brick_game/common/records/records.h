#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_RECORDS_RECORDS_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_RECORDS_RECORDS_H_

#include <stdbool.h>

#define RECORDS_NUMBER (5)
#define TETRIS_RECORDS_FILE_NAME "tetris_records.log"
#define SNAKE_RECORDS_FILE_NAME "snake_xenzia_records.log"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  bool is_current_player_;
  char *name_;
  int score_;
} Record;

typedef struct {
  Record *records_;
} Records;

Records *AllocRecords();
void FreeRecords(Records *);

Record *RecordGetRecordIndex(const Records *records, const int index);
char *RecordGetName(const Record *record);
int RecordGetScore(const Record *record);
int RecordGetIsCurrentPlayer(const Record *record);

void CopyRecord(Record *dest, const Record *src);
void InitRecords(Records *p_records);

void AddRecord(Records *p_records, const char *name, int score,
               const char *filename);
void RemoveRecord(Records *p_records, const char *name, const char *filename);

bool SaveRecords(const Records *p_records, const char *filename);

bool LoadRecords(Records *p_records, const char *filename);

void SortRecords(Records *p_records);
#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_RECORDS_RECORDS_H_
