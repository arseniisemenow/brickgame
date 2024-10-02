#ifndef CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_VIEW_H_
#define CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_VIEW_H_

#include <QInputDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QLayoutItem>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

#include "brick_game/common/fsm_types.h"
#include "brick_game/common/parameters/parameters.h"
#include "brick_game/common/retrieve_data/retrieve_data.h"
#include "brick_game/snake/controller/controller.h"
#include "brick_game/tetris/fsm/fsm.h"
#include "grid_widget/grid_widget.h"
#include "next_player_grid_widget/next_player_grid_widget.hpp"
#include "view_tab_switcher/view_tab_switcher.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

public:
  explicit View(QWidget *parent = nullptr);
  ~View();

  void HandleSignal(SignalType signal_type);
  void UpdateTetris();
  void UpdateSnake();
  void UpdateCarRacing();

signals:
  void SignalMoveUp();
  void SignalMoveDown();
  void SignalMoveLeft();
  void SignalMoveRight();
  void SignalEscapeButton();
  void SignalEnterButton();
  void SignalPauseButton();
  void SignalNoneButton();

protected:
  void keyPressEvent(QKeyEvent *event) override;
private slots:
  void StartTetrisGame();
  void StartSnakeGame();
  void StartCarRacingGame();

private:
  Ui::View *ui_;
  ViewTabSwitcher *view_tab_switcher_;

  SignalType signal_type_{};

  Parameters *p_parameters_ = AllocParameters();
  CarRacingParameters car_racing_game_state_{};

  QTimer *timer_;

  CurrentGame current_game_{CurrentGame::kTetris};

  void InitializeUI();
  static void PrintRecords(QLabel **array, const Records* records);
  void PrintTetrisRecords();
  void PrintSnakeRecords();
  void PrintState(State state, QLabel *label);
};
} // namespace s21
#endif // CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_VIEW_H_
