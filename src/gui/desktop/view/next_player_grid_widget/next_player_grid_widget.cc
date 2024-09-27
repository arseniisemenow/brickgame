#include "next_player_grid_widget.hpp"

NextPlayerGridWidget::NextPlayerGridWidget(QWidget *parent) : QWidget(parent) {
  setFixedSize(PLAYER_BOARD_SIZE * s21::constants::kCellSize,
               PLAYER_BOARD_SIZE * s21::constants::kCellSize);
//  next_player_ = AllocPlayer();
}

void NextPlayerGridWidget::SetPlayer(const Player *next_player) {
  next_player_ = const_cast<Player*>(next_player);
  update();
}

void NextPlayerGridWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.setPen(s21::constants::kColorArray[7]);
  for (int row = 0; row < PLAYER_BOARD_SIZE; ++row) {
    for (int col = 0; col < PLAYER_BOARD_SIZE; ++col) {
      painter.drawRect(col * s21::constants::kCellSize,
                       row * s21::constants::kCellSize,
                       s21::constants::kCellSize, s21::constants::kCellSize);
    }
  }

  for (int row = 0; row < PLAYER_BOARD_SIZE; ++row) {
    for (int col = 0; col < PLAYER_BOARD_SIZE; ++col) {
      if (!next_player_)
        continue;
      if (next_player_->board_->board_[row][col].is_set_) {
        int color = next_player_->board_->board_[row][col].color_;
        auto q_color = s21::constants::kColorArray[color];
        painter.fillRect(
            col * s21::constants::kCellSize, row * s21::constants::kCellSize,
            s21::constants::kCellSize, s21::constants::kCellSize, q_color);
      }
    }

  }
}