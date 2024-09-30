#include "view.h"

#include <QTimer>
#include <QVBoxLayout>

#include "./ui_view.h"
#include "brick_game/common/game_status/game_status.h"
#include "brick_game/common/parameters/parameters.h"
#include "brick_game/common/player/player.h"
#include "brick_game/common/time_handler/time_handler.h"
#include "brick_game/tetris/fsm/fsm.h"
#include "grid_widget/grid_widget.h"
#include "next_player_grid_widget/next_player_grid_widget.hpp"

namespace s21 {

void InitParametersForSnakeBeforeStart(Parameters *p_params) {
  InitBoard(p_params->s_board_);
  InitGameStatus(p_params->s_game_status_);
  InitPlayer(p_params->s_player_);
  SetPlayerPosition(p_params->s_player_, 10, 10);

  p_params->s_player_->snake_length_ = 4;
  p_params->s_player_->direction_ = kDirectionSecond;
  p_params->s_player_->snake_body_[0].x_ = 10 / 2;
  p_params->s_player_->snake_body_[0].y_ = 20 / 2;
  *p_params->s_state_ = kStart;
  InitCell(p_params->s_fruit_);
  // todo: move
  p_params->s_fruit_->y_ = rand() % 10;
  p_params->s_fruit_->x_ = rand() % 20;

  *p_params->s_last_moved_time_ = GetTimeInMS();

  LoadRecords(p_params->s_records_, SNAKE_RECORDS_FILE_NAME);
  SaveRecords(p_params->s_records_, SNAKE_RECORDS_FILE_NAME);
}

void InitParametersForTetrisBeforeStart(Parameters *p_params) {
  InitPlayer(p_params->t_player_);
  InitNextPlayer(p_params->t_next_player_);
  InitBoard(p_params->t_board_);
  InitGameStatus(p_params->t_game_status_);

  *p_params->t_last_moved_time_ = GetTimeInMS();

  LoadRecords(p_params->t_records_, TETRIS_RECORDS_FILE_NAME);
  SaveRecords(p_params->t_records_, TETRIS_RECORDS_FILE_NAME);
}

View::View(QWidget *parent) : QMainWindow(parent), ui_(new Ui::View) {
  ui_->setupUi(this);
  view_tab_switcher_ = new ViewTabSwitcher(ui_, this);
  InitializeUI();

  timer_ = new QTimer(this);

  connect(timer_, &QTimer::timeout, [=]() { HandleSignal(kSignalNone); });

  timer_->start(1);
}

View::~View() {
  delete ui_;
  delete view_tab_switcher_;
  delete timer_;
}

void View::HandleSignal(SignalType signal_type) {
  signal_type_ = signal_type;
  if (current_game_ == CurrentGame::kTetris) {
    UpdateTetris();
  } else if (current_game_ == CurrentGame::kSnake) {
    UpdateSnake();
  }
}

void View::UpdateTetris() {
  SignalType signal = signal_type_;
  SignalAction(signal, p_parameters_);
  PrintState(*p_parameters_->t_state_, ui_->label_state_tetris);
  if (*p_parameters_->t_state_ != kStart &&
      *p_parameters_->t_state_ != kPause) {
    ui_->widget_snake->SetCurrentGame(CurrentGame::kTetris);
    ui_->widget_tetris->SetBoard(p_parameters_->t_board_);
    ui_->widget_tetris->SetPlayer(p_parameters_->t_player_);
    ui_->widget_tetris->SetPredictPlayer(p_parameters_->t_predict_player_);
    ui_->widget_tetris_next_player->SetPlayer(p_parameters_->t_next_player_);
    ui_->label_score_tetris_value->setText(
        QString::number(p_parameters_->t_game_status_->score_, 10));
    ui_->label_level_tetris_value->setText(
        QString::number(p_parameters_->t_game_status_->level_, 10));

    PrintTetrisRecords();
  }
  if (*p_parameters_->t_state_ == kGameOver) {
    bool ok;
    QString name = QInputDialog::getText(this, "Enter Your Name",
                                         "Name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
      RemoveRecord(p_parameters_->t_records_, "Unnamed",
                   TETRIS_RECORDS_FILE_NAME);
      std::string string = name.toStdString();
      const char *c_string = string.c_str();
      AddRecord(p_parameters_->t_records_, c_string,
                p_parameters_->t_game_status_->score_,
                TETRIS_RECORDS_FILE_NAME);
    }
  }
  if (*p_parameters_->t_state_ == kExitState) {
    this->close();
  }
}
void View::UpdateSnake() {
  SignalType signal = signal_type_;
  ControllerSnake(signal, p_parameters_);

  PrintState(*p_parameters_->s_state_, ui_->label_state_snake);
  if (*p_parameters_->s_state_ == kStart) {
    InitParametersForSnakeBeforeStart(p_parameters_);
  }

  if (*p_parameters_->s_state_ != kStart &&
      *p_parameters_->s_state_ != kPause) {
    ui_->widget_snake->SetCurrentGame(CurrentGame::kSnake);
    ui_->widget_snake->SetBoard(p_parameters_->s_board_);
    ui_->widget_snake->SetPlayer(p_parameters_->s_player_);
    ui_->widget_snake->SetFruit(p_parameters_->s_fruit_);
    ui_->label_score_snake_value->setText(
        QString::number(p_parameters_->s_game_status_->score_, 10));
    ui_->label_level_snake_value->setText(
        QString::number(p_parameters_->s_game_status_->level_, 10));

    PrintSnakeRecords();
  }
  if (*p_parameters_->s_state_ == kGameOver) {
    *p_parameters_->s_state_ = kStart;
    bool ok;
    QString name = QInputDialog::getText(this, "Enter Your Name",
                                         "Name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
      RemoveRecord(p_parameters_->s_records_, "Unnamed",
                   SNAKE_RECORDS_FILE_NAME);
      std::string string = name.toStdString();
      const char *c_string = string.c_str();
      AddRecord(p_parameters_->s_records_, c_string,
                p_parameters_->s_game_status_->score_, SNAKE_RECORDS_FILE_NAME);
    }
  }
  if (*p_parameters_->s_state_ == kExitState) {
    this->close();
  }
}

void View::InitializeUI() {
  StartTetrisGame();
  //    StartSnakeGame();

  connect(ui_->push_button_tetris, &QPushButton::clicked, this,
          &View::StartTetrisGame);
  connect(ui_->push_button_snake, &QPushButton::clicked, this,
          &View::StartSnakeGame);

  connect(this, &View::SignalMoveUp, [=]() { HandleSignal(kSignalMoveUp); });
  connect(this, &View::SignalMoveDown,
          [=]() { HandleSignal(kSignalMoveDown); });
  connect(this, &View::SignalMoveLeft,
          [=]() { HandleSignal(kSignalMoveLeft); });
  connect(this, &View::SignalMoveRight,
          [=]() { HandleSignal(kSignalMoveRight); });
  connect(this, &View::SignalEnterButton,
          [=]() { HandleSignal(kSignalEnterButton); });
  connect(this, &View::SignalNoneButton, [=]() { HandleSignal(kSignalNone); });
}
void View::StartTetrisGame() {
  current_game_ = CurrentGame::kTetris;
  InitParametersForTetrisBeforeStart(p_parameters_);
}

void View::StartSnakeGame() {
  current_game_ = CurrentGame::kSnake;
  InitParametersForSnakeBeforeStart(p_parameters_);
}

void View::PrintRecords(QLabel **array, const Records *records) {
  for (int i = 0; i < 5; ++i) {
    auto username = QString(records->records_[i].name_);
    username.truncate(3);
    array[i]->setText(username + " " +
                      QString::number(records->records_[i].score_, 10));
  }
}

void View::PrintTetrisRecords() {
  QLabel *records_labels[5] = {
      ui_->label_records_1_value, ui_->label_records_2_value,
      ui_->label_records_3_value, ui_->label_records_4_value,
      ui_->label_records_5_value};
  PrintRecords(records_labels, p_parameters_->t_records_);
}

void View::PrintSnakeRecords() {
  QLabel* records_labels[] = {
      ui_->label_records_snake_1_value, ui_->label_records_snake_2_value,
      ui_->label_records_snake_3_value, ui_->label_records_snake_4_value,
      ui_->label_records_snake_5_value};
  PrintRecords(records_labels, p_parameters_->s_records_);
}

void View::PrintState(State state, QLabel *label) {
  QString state_string{};
  if (state == kGameOver) {
    state_string = "Game Over";
  } else if (state == kPause) {
    state_string = "Paused";
  } else if (state == kMoving) {
    state_string = "Moving";
  } else if (state == kStart) {
    state_string = "Start";
  } else if (state == kExitState) {
    state_string = "Exit state";
  } else if (state == kSpawn) {
    state_string = "Spawn";
  }
  label->setText(state_string);
}

void View::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W)
    HandleSignal(kSignalMoveUp);
  else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S)
    HandleSignal(kSignalMoveDown);
  else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A)
    HandleSignal(kSignalMoveLeft);
  else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
    HandleSignal(kSignalMoveRight);
  else if (event->key() == Qt::Key_Escape)
    HandleSignal(kSignalEscapeButton);
  else if (event->key() == Qt::Key_Return)
    HandleSignal(kSignalEnterButton);
  else if (event->key() == Qt::Key_P)
    HandleSignal(kSignalPauseButton);
  else {
    QWidget::keyPressEvent(event);
  }
}

} // namespace s21
