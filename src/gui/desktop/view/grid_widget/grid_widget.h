#ifndef CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_GRID_WIDGET_GRID_WIDGET_H_
#define CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_GRID_WIDGET_GRID_WIDGET_H_

#include <QApplication>
#include <QPainter>
#include <QWidget>

#include "brick_game/common/board/board.h"
#include "brick_game/common/player/player.h"
#include "brick_game/common/parameters/parameters.h"

#include "constants.h"

class GridWidget : public QWidget {
 public:
  GridWidget(QWidget *parent = nullptr, int rows = s21::constants::kRows,
             int columns = s21::constants::kColumns);

  void SetBoard(const Board *board);
  void SetPlayer(const Player *player);
  void SetPredictPlayer(const Player *player);
  void SetFruit(const Cell *fruit);
  void SetCurrentGame(s21::CurrentGame current_game);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void DrawPlayer(QPainter *painter, const Player *player);
  void DrawSnakeGame(QPainter *painter, Player *player);

 private:
  Board* board_;
  Player* player_;
  Player* predict_player_;
  Cell* fruit_;
  Car car_;
  Car rival_cars[2];
  int rows_;
  int columns_;
  s21::CurrentGame current_game_{s21::CurrentGame::kTetris};
};

#endif  // CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_GRID_WIDGET_GRID_WIDGET_H_