#include "Action.h"

#include "../move_snake/move_snake.h"

namespace s21 {

void Action::Start(Parameters *p_parameters) {
  *p_parameters->s_state_ = kSpawn;
}
void Action::Spawn(Parameters *p_parameters) {
  InitPlayer(p_parameters->s_player_);
  p_parameters->s_player_->snake_length_ = 4;
  p_parameters->s_game_status_->level_ = 0;
  p_parameters->s_game_status_->score_ = 0;
  for (int i = 3; i >= 0; --i) {
    p_parameters->s_player_->snake_body_[i].x_ = 5;
    p_parameters->s_player_->snake_body_[i].y_ = 5 + i + 1;
  }
  *p_parameters->s_state_ = kMoving;
  p_parameters->s_player_->direction_ = kDirectionSecond;

  MoveFruitToRandomPlace(p_parameters);
}
void Action::MovingUp(Parameters *p_parameters) {
  if (p_parameters->s_player_->direction_ != kDirectionSecond) {
    p_parameters->s_player_->direction_ = kDirectionFirst;
  }
  MoveSnake(p_parameters);
}
void Action::MovingDown(Parameters *p_parameters) {
  if (p_parameters->s_player_->direction_ != kDirectionFirst) {
    p_parameters->s_player_->direction_ = kDirectionSecond;
  }
  MoveSnake(p_parameters);
}
void Action::MovingLeft(Parameters *p_parameters) {
  if (p_parameters->s_player_->direction_ != kDirectionForth) {
    p_parameters->s_player_->direction_ = kDirectionThird;
  }
  MoveSnake(p_parameters);
}
void Action::MovingRight(Parameters *p_parameters) {
  if (p_parameters->s_player_->direction_ != kDirectionThird) {
    p_parameters->s_player_->direction_ = kDirectionForth;
  }
  MoveSnake(p_parameters);
}
void Action::Collide(Parameters *p_parameters) {
  *p_parameters->s_state_ = kGameOver;
}
void Action::GameOver(Parameters *p_parameters) {
  *p_parameters->t_state_ = *p_parameters->t_state_;
}
void Action::Exit(Parameters *p_parameters) {
  *p_parameters->s_state_ = kExitState;
}
void Action::Pause(Parameters *p_parameters) {
  if (*p_parameters->s_state_ == kPause) {
    *p_parameters->s_state_ = kMoving;
  } else if (*p_parameters->s_state_ == kMoving) {
    *p_parameters->s_state_ = kPause;
  }
}
}  // namespace s21
