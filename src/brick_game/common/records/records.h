#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_RECORDS_RECORDS_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_RECORDS_RECORDS_H_

#include <stdbool.h>

#define RECORDS_NUMBER (5)
#define TETRIS_RECORDS_FILE_NAME "tetris_records.records_"
#define SNAKE_RECORDS_FILE_NAME "snake_xerzia_records.records_"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  bool is_current_player_;
  char name_[20];
  int score_;
} Record;

typedef struct {
  Record records_[RECORDS_NUMBER];
} Records;

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
