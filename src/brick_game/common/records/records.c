#include "records.h"

#include <stdio.h>
#include <string.h>

void InitRecords(Records *p_records) {
  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    p_records->records_[i].is_current_player_ = false;
    p_records->records_[i].score_ = 0;
    p_records->records_[i].name_[0] = '\0';
  }
}

void AddRecord(Records *p_records, const char *name, int score,
               const char *filename) {
  if (strlen(name) == 0) {
    return;
  }
  bool flag_handled = false;
  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    if (strcmp(p_records->records_[i].name_, name) == 0) {
      if (score > p_records->records_[i].score_) {
        p_records->records_[i].score_ = score;
      }
      flag_handled = true;
    }
  }

  int position = RECORDS_NUMBER - 1;
  for (int i = RECORDS_NUMBER - 1; i >= 0 && !flag_handled; --i) {
    if (score > p_records->records_[i].score_) {
      position = i;
    } else {
      break;
    }
  }

  for (int i = RECORDS_NUMBER - 1; i > position && !flag_handled; --i) {
    p_records->records_[i] = p_records->records_[i - 1];
  }

  if (!flag_handled) {
    p_records->records_[position].is_current_player_ = true;
    p_records->records_[position].score_ = score;
    snprintf(p_records->records_[position].name_, 18, "%s", name);
  }
  SortRecords(p_records);
  SaveRecords(p_records, filename);
  LoadRecords(p_records, filename);
}

void RemoveRecord(Records *p_records, const char *name, const char *filename) {
  bool found = false;
  int i;

  for (i = 0; i < RECORDS_NUMBER; ++i) {
    if (strcmp(p_records->records_[i].name_, name) == 0) {
      found = true;
      break;
    }
  }

  if (found) {
    for (int j = i; j < RECORDS_NUMBER - 1; ++j) {
      p_records->records_[j] = p_records->records_[j + 1];
    }

    p_records->records_[RECORDS_NUMBER - 1].is_current_player_ = false;
    p_records->records_[RECORDS_NUMBER - 1].score_ = 0;
    p_records->records_[RECORDS_NUMBER - 1].name_[0] = '\0';
  }
  SortRecords(p_records);
  SaveRecords(p_records, filename);
  LoadRecords(p_records, filename);
}

bool SaveRecords(const Records *p_records, const char *filename) {
  FILE *p_file = fopen(filename, "wb");
  if (!p_file) {
    return false;
  }

  size_t num_written = fwrite(p_records, sizeof(Records), 1, p_file);
  fclose(p_file);

  return num_written == 1;
}

bool LoadRecords(Records *p_records, const char *filename) {
  FILE *p_file = fopen(filename, "rb");
  if (!p_file) {
    return false;
  }

  size_t num_read = fread(p_records, sizeof(Records), 1, p_file);
  fclose(p_file);

  return num_read == 1;
}

void SortRecords(Records *p_records) {
  bool swapped = false;

  do {
    swapped = false;
    for (int i = 0; i < RECORDS_NUMBER - 1; ++i) {
      if (p_records->records_[i].score_ < p_records->records_[i + 1].score_) {
        Record temp_record = p_records->records_[i];
        p_records->records_[i] = p_records->records_[i + 1];
        p_records->records_[i + 1] = temp_record;
        swapped = true;
      }
    }
  } while (swapped);
}