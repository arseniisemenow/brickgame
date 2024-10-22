#include "game_status.h"

#include <stdlib.h>

GameStatus *AllocGameStatus() {
  return (GameStatus *)calloc(sizeof(GameStatus), 1);
}
void FreeGameStatus(GameStatus *p_game_status) { free(p_game_status); }

int GameStateGetScore(const GameStatus *p_game_status) {
  return p_game_status->score_;
}
int GameStateGetLevel(const GameStatus *p_game_status) {
  return p_game_status->level_;
}

void InitGameStatus(GameStatus *p_game_status) {
  p_game_status->level_ = 0;
  p_game_status->score_ = 0;
}

void AddScoreGameStatus(GameStatus *p_game_status, int complete_lines_count) {
  if (complete_lines_count <= 0) {
    return;
  }
  if (complete_lines_count > MAX_AVAILABLE_COMPLETE_LINES_COUNT) {
    complete_lines_count = MAX_AVAILABLE_COMPLETE_LINES_COUNT;
  }
  int earned_score = kScoreCompleteLinesCountArray[complete_lines_count - 1];
  p_game_status->score_ += earned_score;
}

void UpdateGameStatusLevel(GameStatus *p_game_status) {
  int current_level = (p_game_status->score_ / SCORE_PER_LEVEL);

  if (current_level > MAX_LEVEL) {
    current_level = MAX_LEVEL;
  }
  p_game_status->level_ = current_level;
}