#include "move_snake.h"

#include <cstdlib>

namespace s21 {

void MoveFruitToRandomPlace(Parameters *p_parameters) {
  p_parameters->s_fruit_->x_ = (rand() % p_parameters->s_board_->width_);
  p_parameters->s_fruit_->y_ = (rand() % p_parameters->s_board_->height_);
}

int CalculateLevel(const Parameters *p_parameters) {
  return p_parameters->s_game_status_->score_ / 5;
}

void EatFruit(Parameters *p_parameters) {
  p_parameters->s_player_->snake_length_++;
  p_parameters->s_game_status_->score_++;
  p_parameters->s_game_status_->level_ = CalculateLevel(p_parameters);
}

void HandleMoveTail(Parameters *p_parameters) {
  for (int i = p_parameters->s_player_->snake_length_ - 1; i > 0; --i) {
    p_parameters->s_player_->snake_body_[i] =
        p_parameters->s_player_->snake_body_[i - 1];
  }
}
void HandleMoveHead(Parameters *p_parameters) {
  if (p_parameters->s_player_->direction_ == kDirectionFirst) {
    p_parameters->s_player_->snake_body_[0].y_--;
  } else if (p_parameters->s_player_->direction_ == kDirectionSecond) {
    p_parameters->s_player_->snake_body_[0].y_++;

  } else if (p_parameters->s_player_->direction_ == kDirectionThird) {
    p_parameters->s_player_->snake_body_[0].x_--;

  } else if (p_parameters->s_player_->direction_ == kDirectionForth) {
    p_parameters->s_player_->snake_body_[0].x_++;
  }
}
bool GetFlagEatFruitX(const Parameters *p_parameters) {
  bool flag =
      p_parameters->s_player_->snake_body_[0].x_ == p_parameters->s_fruit_->x_;
  return flag;
}
bool GetFlagEatFruitY(const Parameters *p_parameters) {
  bool flag =
      p_parameters->s_player_->snake_body_[0].y_ == p_parameters->s_fruit_->y_;
  return flag;
}

void HandleEatFruit(Parameters *p_parameters) {
  bool flag_eat_fruit_x = GetFlagEatFruitX(p_parameters);
  bool flag_eat_fruit_y = GetFlagEatFruitY(p_parameters);
  bool flag_eat_fruit = flag_eat_fruit_x && flag_eat_fruit_y;
  if (flag_eat_fruit) {
    EatFruit(p_parameters);
    MoveFruitToRandomPlace(p_parameters);
    AddRecord(p_parameters->s_records_, "Unnamed",
              p_parameters->s_game_status_->score_, SNAKE_RECORDS_FILE_NAME);
    if (p_parameters->s_player_->snake_length_ >= 200) {
      *p_parameters->s_state_ = kGameOver;
    }
  }
}

bool GetFlagCollideWithHeadX(const Parameters *p_parameters, int i) {
  bool flag = p_parameters->s_player_->snake_body_[0].x_ ==
              p_parameters->s_player_->snake_body_[i].x_;
  return flag;
}
bool GetFlagCollideWithHeadY(const Parameters *p_parameters, int i) {
  bool flag = p_parameters->s_player_->snake_body_[0].y_ ==
              p_parameters->s_player_->snake_body_[i].y_;
  return flag;
}
void HandleCollideWithItself(Parameters *p_parameters) {
  int first_segment_to_collide_index = 4;
  for (int i = first_segment_to_collide_index;
       i < p_parameters->s_player_->snake_length_; ++i) {
    bool flag_collide_with_head_x = GetFlagCollideWithHeadX(p_parameters, i);
    bool flag_collide_with_head_y = GetFlagCollideWithHeadY(p_parameters, i);
    bool is_collide_with_head =
        (flag_collide_with_head_x && flag_collide_with_head_y);
    if (is_collide_with_head) {
      *p_parameters->s_state_ = kCollide;
      break;
    }
  }
}
void MoveSnake(Parameters *p_parameters) {
  HandleMoveTail(p_parameters);
  HandleMoveHead(p_parameters);
  HandleEatFruit(p_parameters);
  HandleCollideWithWall(p_parameters);
  HandleCollideWithItself(p_parameters);
}
bool GetFlagCollideWallX(const Parameters *p_parameters) {
  bool flag_collide_with_left = p_parameters->s_player_->snake_body_[0].x_ < 0;
  bool flag_collide_with_right = p_parameters->s_player_->snake_body_[0].x_ >=
                                 p_parameters->s_board_->width_;
  bool flag = flag_collide_with_left || flag_collide_with_right;
  return flag;
}
bool GetFlagCollideWallY(const Parameters *p_parameters) {
  bool flag_collide_with_up = p_parameters->s_player_->snake_body_[0].y_ < 0;
  bool flag_collide_with_down = p_parameters->s_player_->snake_body_[0].y_ >=
                                p_parameters->s_board_->height_;
  bool flag = flag_collide_with_up || flag_collide_with_down;
  return flag;
}

void HandleCollideWithWall(Parameters *p_parameters) {
  bool flag_collide_wall_x = GetFlagCollideWallX(p_parameters);
  bool flag_collide_wall_y = GetFlagCollideWallY(p_parameters);
  bool is_collide_wall = flag_collide_wall_x || flag_collide_wall_y;
  if (is_collide_wall) {
    *p_parameters->s_state_ = kCollide;
  }
}

}  // namespace s21
