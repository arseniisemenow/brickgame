#include "view.h"

#include <QTimer>
#include <QVBoxLayout>

#include "brick_game/common/game_status/game_status.h"
#include "brick_game/common/parameters/parameters.h"
#include "brick_game/common/player/player.h"
#include "brick_game/common/time_handler/time_handler.h"
#include "brick_game/tetris/fsm/fsm.h"
#include "grid_widget/grid_widget.h"
#include "next_player_grid_widget/next_player_grid_widget.hpp"
#include "./ui_View.h"

namespace s21 {
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
  SignalAction(signal, p_t_parameters_);
  PrintState(*p_t_parameters_->t_state_, ui_->label_state_tetris);
  if (*p_t_parameters_->t_state_ != kStart &&
      *p_t_parameters_->t_state_ != kPause) {
    ui_->widget_snake->SetCurrentGame(CurrentGame::kTetris);
    ui_->widget_tetris->SetBoard(*p_t_parameters_->t_board_);
    ui_->widget_tetris->SetPlayer(*p_t_parameters_->t_player_);
    ui_->widget_tetris->SetPredictPlayer(*p_t_parameters_->t_predict_player_);
    ui_->widget_tetris_next_player->SetPlayers(
        *p_t_parameters_->t_next_player_);
    ui_->label_score_tetris_value->setText(
        QString::number(p_t_parameters_->t_game_status_->score_, 10));
    ui_->label_level_tetris_value->setText(
        QString::number(p_t_parameters_->t_game_status_->level_, 10));

    PrintTetrisRecords();
  }
  if (*p_t_parameters_->t_state_ == kGameOver) {
    bool ok;
    QString name = QInputDialog::getText(this, "Enter Your Name",
                                         "Name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
      RemoveRecord(p_t_parameters_->t_records_, "Unnamed",
                   TETRIS_RECORDS_FILE_NAME);
      std::string string = name.toStdString();
      const char *c_string = string.c_str();
      AddRecord(p_t_parameters_->t_records_, c_string,
                p_t_parameters_->t_game_status_->score_,
                TETRIS_RECORDS_FILE_NAME);
    }
  }
  if (*p_t_parameters_->t_state_ == kExitState) {
    this->close();
  }
}
void View::UpdateSnake() {
  SignalType signal = signal_type_;
  ControllerSnake(signal, p_s_parameters_);

  PrintState(*p_s_parameters_->s_state_, ui_->label_state_snake);

  if (*p_s_parameters_->s_state_ != kStart &&
      *p_s_parameters_->s_state_ != kPause) {
    ui_->widget_snake->SetCurrentGame(CurrentGame::kSnake);
    ui_->widget_snake->SetBoard(*p_s_parameters_->s_board_);
    ui_->widget_snake->SetPlayer(*p_s_parameters_->s_player_);
    ui_->widget_snake->SetFruit(*p_s_parameters_->s_fruit_);
    ui_->label_score_snake_value->setText(
        QString::number(p_s_parameters_->s_game_status_->score_, 10));
    ui_->label_level_snake_value->setText(
        QString::number(p_s_parameters_->s_game_status_->level_, 10));

    PrintSnakeRecords();
  }
  if (*p_s_parameters_->s_state_ == kGameOver) {
    bool ok;
    QString name = QInputDialog::getText(this, "Enter Your Name",
                                         "Name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
      RemoveRecord(p_s_parameters_->s_records_, "Unnamed",
                   SNAKE_RECORDS_FILE_NAME);
      std::string string = name.toStdString();
      const char *c_string = string.c_str();
      AddRecord(p_s_parameters_->s_records_, c_string,
                p_s_parameters_->s_game_status_->score_,
                SNAKE_RECORDS_FILE_NAME);
      *p_s_parameters_->s_state_ = kStart;
    }
  }
  if (*p_s_parameters_->s_state_ == kExitState) {
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
  InitBoard(&t_board_);
  InitPlayer(&t_player_);
  InitPlayerPosition(&t_player_);
  t_state_ = kStart;

  InitGameStatus(&game_status_);
  InitPlayer(&t_player_);
  InitNextPlayer(&t_next_player_);
  InitBoard(&t_board_);
  //            PrintBegin();
  t_time_in_secs_ = GetTimeInMS();

  t_parameters_.t_game_status_ = &game_status_;
  t_parameters_.t_state_ = &t_state_;
  t_parameters_.t_board_ = &t_board_;
  t_parameters_.t_player_ = &t_player_;
  t_parameters_.t_next_player_ = &t_next_player_;
  t_parameters_.t_predict_player_ = &t_predict_player_;
  t_parameters_.t_last_moved_time_ = &t_time_in_secs_;
  t_parameters_.t_records_ = &t_records_;

  LoadRecords(t_parameters_.t_records_, TETRIS_RECORDS_FILE_NAME);
  SaveRecords(t_parameters_.t_records_, TETRIS_RECORDS_FILE_NAME);

  p_t_parameters_ = &t_parameters_;
}
void View::StartSnakeGame() {
  current_game_ = CurrentGame::kSnake;
  InitBoard(&s_board_);
  InitGameStatus(&s_game_status_);

  InitPlayer(&s_player_);
  SetPlayerPosition(&s_player_, 10, 10);
  s_state_ = kStart;
  s_player_.snake_length_ = 4;
  s_player_.direction_ = kDirectionSecond;
  s_player_.snake_body_[0].x_ = 10 / 2;
  s_player_.snake_body_[0].y_ = 20 / 2;

  InitCell(&s_fruit_);
  s_fruit_.y_ = rand() % 10;
  s_fruit_.x_ = rand() % 20;
  s_time_in_secs_ = GetTimeInMS();

  s_parameters_.s_state_ = &s_state_;
  s_parameters_.s_player_ = &s_player_;
  s_parameters_.s_fruit_ = &s_fruit_;
  s_parameters_.s_game_status_ = &s_game_status_;
  s_parameters_.s_board_ = &s_board_;
  s_parameters_.s_records_ = &s_records_;
  s_parameters_.s_last_moved_time_ = &s_time_in_secs_;
  LoadRecords(s_parameters_.s_records_, SNAKE_RECORDS_FILE_NAME);
  SaveRecords(s_parameters_.s_records_, SNAKE_RECORDS_FILE_NAME);

  p_s_parameters_ = &s_parameters_;
}
void View::PrintTetrisRecords() {
  auto records = p_t_parameters_->t_records_;
  ui_->label_records_1_value->setText(
      QString::number(records->records_[0].score_, 10));
  ui_->label_records_2_value->setText(
      QString::number(records->records_[1].score_, 10));
  ui_->label_records_3_value->setText(
      QString::number(records->records_[2].score_, 10));
  ui_->label_records_4_value->setText(
      QString::number(records->records_[3].score_, 10));
  ui_->label_records_5_value->setText(
      QString::number(records->records_[4].score_, 10));
}
void View::PrintSnakeRecords() {
  auto records = p_s_parameters_->s_records_;
  ui_->label_records_snake_1_value->setText(
      QString::number(records->records_[0].score_, 10));
  ui_->label_records_snake_2_value->setText(
      QString::number(records->records_[1].score_, 10));
  ui_->label_records_snake_3_value->setText(
      QString::number(records->records_[2].score_, 10));
  ui_->label_records_snake_4_value->setText(
      QString::number(records->records_[3].score_, 10));
  ui_->label_records_snake_5_value->setText(
      QString::number(records->records_[4].score_, 10));
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

}  // namespace s21
