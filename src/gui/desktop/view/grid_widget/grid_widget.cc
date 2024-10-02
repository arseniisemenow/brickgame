#include "grid_widget.h"

GridWidget::GridWidget(QWidget *parent, int rows, int columns)
    : QWidget(parent), rows_(rows), columns_(columns) {
  setFixedSize(columns_ * s21::constants::kCellSize,
               rows_ * s21::constants::kCellSize);
  board_ = AllocBoard(); //todo: free
  player_ = AllocPlayer();
  predict_player_ = AllocPlayer();
  fruit_ = AllocCell();
}

void GridWidget::SetBoard(const Board *board) {
  board_ = const_cast<Board*>(board);
  update();
}
void GridWidget::SetPlayer(const Player *player) {
  player_ = const_cast<Player*>(player);
  update();
}
void GridWidget::SetPredictPlayer(const Player *player) {
  predict_player_ = const_cast<Player*>(player);
  update();
}
void GridWidget::SetFruit(const Cell *fruit) {
  fruit_ = const_cast<Cell*>(fruit);
  update();
}
void GridWidget::SetCurrentGame(s21::CurrentGame current_game) {
  current_game_ = current_game;
}

void GridWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  // Draw grid
  painter.setPen(s21::constants::kColorArray[7]);
  for (int row = 0; row < s21::constants::kRows; ++row) {
    for (int col = 0; col < s21::constants::kColumns; ++col) {
      painter.drawRect(col * s21::constants::kCellSize,
                       row * s21::constants::kCellSize,
                       s21::constants::kCellSize, s21::constants::kCellSize);
    }
  }

  for (int row = 0; row < s21::constants::kRows; ++row) {
    for (int col =  0; col < s21::constants::kColumns; ++col) {
      if (!board_)
        continue;
      if (!board_->cells_)
        continue;
      if (board_->cells_[row][col].is_set_) {
        int color = board_->cells_[row][col].color_;
        auto q_color = s21::constants::kColorArray[color];
        painter.fillRect(
            col * s21::constants::kCellSize, row * s21::constants::kCellSize,
            s21::constants::kCellSize, s21::constants::kCellSize, q_color);
      }
    }
  }
  if (current_game_ == s21::CurrentGame::kTetris){
     DrawPlayer(&painter, predict_player_);
     DrawPlayer(&painter, player_);
  } else if (current_game_ == s21::CurrentGame::kSnake){
     DrawSnakeGame(&painter, player_);
  }

}

void GridWidget::DrawPlayer(QPainter *painter, const Player *player) {
  if (!player)
    return;
  int player_pos_x = player->x_;
  int player_pos_y = player->y_;
  PlayerBoard *player_board = player->board_;

  for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
    for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
         ++column_index) {
      int print_y = player_pos_y + row_index;
      int print_x = player_pos_x + column_index;
      if (!player_board)
        continue;
      if (player_board->board_[row_index][column_index].is_set_) {
        int color = player_board->board_[row_index][column_index].color_;
        auto q_color = s21::constants::kColorArray[color];
        painter->fillRect(print_x * s21::constants::kCellSize,
                          print_y * s21::constants::kCellSize,
                          s21::constants::kCellSize, s21::constants::kCellSize,
                          q_color);
      }
    }
  }
}
void GridWidget::DrawSnakeGame(QPainter *painter, Player *player) {
  if (!player)
    return;
  if (!board_)
    return;
  if (current_game_ == s21::CurrentGame::kSnake) {
    for (int y = 0; y < board_->height_; ++y) {
      for (int x = 0; x < board_->width_; ++x) {
        bool is_snake_body = false;
        for (int i = 0; i < player->snake_length_; ++i) {
          if (player->snake_body_[i].x_ == x &&
              player->snake_body_[i].y_ == y) {
            painter->fillRect(
                x * s21::constants::kCellSize, y * s21::constants::kCellSize,
                s21::constants::kCellSize, s21::constants::kCellSize,
                QColor(50, 210, 50, 255));
            is_snake_body = true;
            break;
          }
        }
        if (!is_snake_body && x == fruit_->x_ && y == fruit_->y_) {
          painter->fillRect(
              x * s21::constants::kCellSize, y * s21::constants::kCellSize,
              s21::constants::kCellSize, s21::constants::kCellSize,
              QColor(210, 50, 50, 255));
        }
        if (is_snake_body && x == fruit_->x_ && y == fruit_->y_) {
          painter->fillRect(
              x * s21::constants::kCellSize, y * s21::constants::kCellSize,
              s21::constants::kCellSize, s21::constants::kCellSize,
              QColor(70, 150, 70, 255));
        }
      }
    }
  }
}
