#ifndef CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_NEXT_PLAYER_GRID_WIDGET_NEXT_PLAYER_GRID_WIDGET_H_
#define CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_NEXT_PLAYER_GRID_WIDGET_NEXT_PLAYER_GRID_WIDGET_H_


#include <QApplication>
#include <QPainter>
#include <QWidget>

#include "brick_game/common/board/board.h"
#include "brick_game/common/player/player.h"
#include "constants.h"

class NextPlayerGridWidget : public QWidget {
 public:
  NextPlayerGridWidget(QWidget *parent = nullptr);

  void SetPlayer(const Player *next_player);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  Player *next_player_;
};

#endif //CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_NEXT_PLAYER_GRID_WIDGET_NEXT_PLAYER_GRID_WIDGET_H_