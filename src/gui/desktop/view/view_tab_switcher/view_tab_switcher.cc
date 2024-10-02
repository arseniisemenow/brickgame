#include "view_tab_switcher.h"

#include <QObject>

#include "style_handler/style_handler.h"

namespace s21 {

inline constexpr int kTetrisTabIndex = 0;
inline constexpr int kSnakeTabIndex = 1;
inline constexpr int kCarRacingTabIndex = 2;
inline constexpr int kTankClassicTabIndex = 3;

ViewTabSwitcher::ViewTabSwitcher(Ui::View *ui, QWidget *parent)
    : ui_(ui), parent_(parent) {
  SetButtons();
};

void ViewTabSwitcher::SetButtons() {
  InitStackedWidgetIndex();

  connect(ui_->push_button_tetris, &QPushButton::clicked, this,
          &ViewTabSwitcher::SetExpressionCurrentIndex);
  connect(ui_->push_button_snake, &QPushButton::clicked, this,
          &ViewTabSwitcher::SetGraphCurrentIndex);
  connect(ui_->push_button_car_racing, &QPushButton::clicked, this,
          &ViewTabSwitcher::SetCreditCurrentIndex);
  connect(ui_->push_button_tank_classic, &QPushButton::clicked, this,
          &ViewTabSwitcher::SetDepositCurrentIndex);

  ui_->push_button_tank_classic->setDisabled(true);
  SetExpressionCurrentIndex();
}

void ViewTabSwitcher::InitStackedWidgetIndex() {
  SetStyle(ui_->push_button_tetris);
  ui_->stacked_widget->setCurrentIndex(kTetrisTabIndex);
}

void ViewTabSwitcher::SetExpressionCurrentIndex() {
  auto push_button = qobject_cast<QPushButton *>(sender());
  if (push_button) {
    SetStyle(push_button);
    ui_->stacked_widget->setCurrentIndex(kTetrisTabIndex);
  }
}
void ViewTabSwitcher::SetGraphCurrentIndex() {
  auto push_button = qobject_cast<QPushButton *>(sender());
  if (push_button) {
    SetStyle(push_button);
    ui_->stacked_widget->setCurrentIndex(kSnakeTabIndex);
  }
}
void ViewTabSwitcher::SetCreditCurrentIndex() {
  auto push_button = qobject_cast<QPushButton *>(sender());
  if (push_button) {
    SetStyle(push_button);
    ui_->stacked_widget->setCurrentIndex(kCarRacingTabIndex);
  }
}
void ViewTabSwitcher::SetDepositCurrentIndex() {
  auto push_button = qobject_cast<QPushButton *>(sender());
  if (push_button) {
    SetStyle(push_button);
    ui_->stacked_widget->setCurrentIndex(kTankClassicTabIndex);
  }
}
void ViewTabSwitcher::SetStyle(QPushButton *push_button) {
  style_handler::SetUnselectedTabButton(ui_->push_button_tetris);
  style_handler::SetUnselectedTabButton(ui_->push_button_snake);
  style_handler::SetUnselectedTabButton(ui_->push_button_car_racing);
  style_handler::SetUnselectedTabButton(ui_->push_button_tank_classic);
  if (push_button) {
    style_handler::SetSelectedTabButton(push_button);
  }
}
}  // namespace s21
