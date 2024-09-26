#include "game_status.h"

void InitGameStatus(GameStatus* p_game_status) {
  p_game_status->level_ = 0;
  p_game_status->score_ = 0;
}

void AddScoreGameStatus(GameStatus* p_game_status, int complete_lines_count) {
  if (complete_lines_count <= 0) {
    return;
  }
  if (complete_lines_count > MAX_AVAILABLE_COMPLETE_LINES_COUNT) {
    complete_lines_count = MAX_AVAILABLE_COMPLETE_LINES_COUNT;
  }
  int earned_score = kScoreCompleteLinesCountArray[complete_lines_count - 1];
  p_game_status->score_ += earned_score;
}

void UpdateGameStatusLevel(GameStatus* p_game_status) {
  int current_level = (p_game_status->score_ / SCORE_PER_LEVEL);

  if (current_level > MAX_LEVEL) {
    current_level = MAX_LEVEL;
  }
  p_game_status->level_ = current_level;
}