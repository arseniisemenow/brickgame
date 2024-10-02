#include <gtest/gtest.h>

#include "../src/brick_game/snake/controller/controller.h"
#include "../src/brick_game/tetris/backend/backend.h"

namespace s21 {
class ModelTest : public ::testing::Test {
protected:
  SignalType signal_type{};
  Parameters *parameters = AllocParameters();

  void SetUp() override {
    signal_type = kSignalNone;
    InitBoard(parameters->s_board_);
    InitGameStatus(parameters->s_game_status_);
    InitPlayer(parameters->s_player_);
    SetPlayerPosition(parameters->s_player_, 10, 10);
    parameters->s_player_->snake_length_ = 4;
    parameters->s_player_->direction_ = kDirectionSecond;
    parameters->s_player_->snake_body_[0].x_ = 10 / 2;
    parameters->s_player_->snake_body_[0].y_ = 20 / 2;

    InitCell(parameters->s_fruit_);
    parameters->s_fruit_->y_ = rand() % 10;
    parameters->s_fruit_->x_ = rand() % 20;

    *parameters->s_last_moved_time_ = GetTimeInMS();
  }
};

TEST_F(ModelTest, EnterTest) {
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  ASSERT_EQ(*parameters->s_state_, kMoving);
}

TEST_F(ModelTest, ExitTest) {
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalEscapeButton;
  ControllerSnake(signal_type, parameters);
  ASSERT_EQ(*parameters->s_state_, kExitState);
}

TEST_F(ModelTest, MoveLeftTest) {
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);

  ASSERT_EQ(*parameters->s_state_, kGameOver);
}

TEST_F(ModelTest, MoveUpTest) {
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);

  ASSERT_EQ(*parameters->s_state_, kGameOver);
}

TEST_F(ModelTest, MoveRightTest) {
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);

  ASSERT_EQ(*parameters->s_state_, kGameOver);
}
TEST_F(ModelTest, PauseTest) {
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalPauseButton;
  ControllerSnake(signal_type, parameters);

  ASSERT_EQ(*parameters->s_state_, kPause);

  signal_type = kSignalPauseButton;
  ControllerSnake(signal_type, parameters);
  ASSERT_EQ(*parameters->s_state_, kMoving);
}

TEST_F(ModelTest, BoardOverlayBlockTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitBoard(board);
  SetPlayerBlockType(player, kBlockO);
  SetPlayerBoardBlock(player->board_, kBlockO, kDirectionFirst);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (player->board_->board_[i][j].is_set_) {
        ASSERT_GE(board->cells_[player->y_ + i][player->x_ + j].is_set_, 0);
      }
    }
  }
}
TEST_F(ModelTest, BoardOverlayBlockOnAnotherBlockTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitBoard(board);

  SetPlayerBlockType(player, kBlockO);
  SetPlayerBoardBlock(player->board_, kBlockO, kDirectionFirst);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);

  SetPlayerBlockType(player, kBlockO);
  SetPlayerBoardBlock(player->board_, kBlockO, kDirectionFirst);
  InitPlayerPosition(player);

  MovePredictPlayerDown(player, board);
  BoardOverlayBlock(player, board);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (player->board_->board_[i][j].is_set_) {
        ASSERT_GE(board->cells_[player->y_ + i][player->x_ + j].is_set_, 0);
      }
    }
  }
}

TEST_F(ModelTest, UpdatePredictPlayerTest) {
  Player *player = AllocPlayer();
  Player *predict_player = AllocPlayer();
  Board *board = AllocBoard();

  InitBoard(board);
  InitPlayerPosition(player);
  SetPlayerBlockType(player, kBlockJ);
  SetPlayerBoardBlock(player->board_, kBlockJ, kDirectionFirst);
  UpdatePredictPlayer(predict_player, player, board);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ASSERT_EQ(predict_player->x_, player->x_);
      ASSERT_GE(predict_player->y_, -1);
      ASSERT_GE(player->y_, -1);
    }
  }
}

TEST_F(ModelTest, GetTimeStepMSTest) {
  GameStatus game_status{};
  game_status.level_ = 0;
  long long time_step_ms = GetTimeStepMS(&game_status);
  ASSERT_EQ(time_step_ms, 1000);
  game_status.level_ = 1;
  time_step_ms = GetTimeStepMS(&game_status);
  ASSERT_EQ(time_step_ms, 875);
  game_status.level_ = 2;
  time_step_ms = GetTimeStepMS(&game_status);
  ASSERT_EQ(time_step_ms, 625);
}

TEST_F(ModelTest, GetRandomBlockTypeTest) {
  BlockType block_type = kBlockI;
  block_type = GetRandomBlockType();
  ASSERT_GE(block_type, 0);
}

TEST_F(ModelTest, GetNextBlockRotationTest) {
  Direction block_rotation = kDirectionFirst;
  block_rotation = GetNextBlockRotation(block_rotation);
  ASSERT_EQ(block_rotation, kDirectionSecond);
  block_rotation = GetNextBlockRotation(block_rotation);
  ASSERT_EQ(block_rotation, kDirectionThird);
  block_rotation = GetNextBlockRotation(block_rotation);
  ASSERT_EQ(block_rotation, kDirectionForth);
}

TEST_F(ModelTest, GetPreviousBlockRotationTest) {
  Direction block_rotation = kDirectionFirst;
  block_rotation = GetPreviousBlockRotation(block_rotation);
  ASSERT_EQ(block_rotation, kDirectionForth);
  block_rotation = GetPreviousBlockRotation(block_rotation);
  ASSERT_EQ(block_rotation, kDirectionThird);
  block_rotation = GetPreviousBlockRotation(block_rotation);
  ASSERT_EQ(block_rotation, kDirectionSecond);
  block_rotation = GetPreviousBlockRotation(block_rotation);
  ASSERT_EQ(block_rotation, kDirectionFirst);
}

TEST_F(ModelTest, HandleBoardCompleteLinesTest) {
  Board *board = AllocBoard();
  board->width_ = 10;
  board->height_ = 20;

  for (int i = 0; i < board->width_; ++i) {
    board->cells_[19][i].is_set_ = true;
  }
  for (int i = 0; i < board->width_; ++i) {
    board->cells_[18][i].is_set_ = true;
  }
  for (int i = 0; i < board->width_; i++) {
    board->cells_[17][i].is_set_ = true;
  }
  for (int i = 0; i < board->width_; i += 2) {
    board->cells_[16][i].is_set_ = true;
  }
  int complete_lines = HandleBoardCompleteLines(board);
  ASSERT_EQ(complete_lines, 3);
}

TEST_F(ModelTest, CheckCollideTest1) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBoardBlock(player->board_, kBlockT, kDirectionFirst);
  bool flag = CheckCollide(player, board);
  ASSERT_EQ(flag, false);
}

TEST_F(ModelTest, CheckFutureCollideWithBlocksLeftTest1) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);

  SetPlayerBlockType(player, kBlockO);
  SetPlayerBoardBlock(player->board_, kBlockO, kDirectionFirst);
  bool flag = CheckFutureCollideWithBlocksLeft(player, board);
  ASSERT_EQ(flag, false);
}

TEST_F(ModelTest, CheckFutureCollideWithBlocksRightTest1) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);
  SetPlayerBlockType(player, kBlockT);
  SetPlayerBoardBlock(player->board_, kBlockT, kDirectionFirst);
  bool flag = CheckFutureCollideWithBlocksRight(player, board);
  ASSERT_EQ(flag, false);
}

TEST_F(ModelTest, CheckFutureCollideWithBlocksLeftTest2) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);
  for (int i = 0; i < board->height_; ++i) {
    board->cells_[i][0].is_set_ = true;
  }

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBoardBlock(player->board_, kBlockT, kDirectionFirst);

  MovePlayerLeft(player);
  MovePlayerLeft(player);
  MovePlayerLeft(player);
  bool flag = CheckFutureCollideWithBlocksLeft(player, board);
  ASSERT_EQ(flag, true);
}
TEST_F(ModelTest, CheckFutureCollideWithBlocksRightTest2) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);
  for (int i = 0; i < board->height_; ++i) {
    board->cells_[i][board->width_ - 1].is_set_ = true;
  }

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBoardBlock(player->board_, kBlockT, kDirectionFirst);

  MovePlayerRight(player);
  MovePlayerRight(player);
  bool flag = CheckFutureCollideWithBlocksRight(player, board);
  ASSERT_EQ(flag, true);
}

TEST_F(ModelTest, CheckFutureCollideWithLeftTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBoardBlock(player->board_, kBlockT, kDirectionFirst);
  MovePlayerLeft(player);
  MovePlayerLeft(player);
  MovePlayerLeft(player);
  MovePlayerLeft(player);

  bool flag = CheckFutureCollideWithLeft(player, board);
  ASSERT_EQ(flag, true);
}

TEST_F(ModelTest, CheckFutureCollideWithRightTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBoardBlock(player->board_, kBlockT, kDirectionFirst);
  MovePlayerRight(player);
  MovePlayerRight(player);
  MovePlayerRight(player);

  bool flag = CheckFutureCollideWithRight(player, board);
  ASSERT_EQ(flag, true);
}

TEST_F(ModelTest, CheckFutureCollideWithUpTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBoardBlock(player->board_, kBlockT, kDirectionFirst);
  MovePlayerRight(player);
  MovePlayerRight(player);
  MovePlayerRight(player);

  bool flag = CheckFutureCollideWithUp(player, board);
  ASSERT_EQ(flag, false);
}

TEST_F(ModelTest, CheckFutureCollideWithDownTest) {
  Player *player = AllocPlayer();
  Board *board = AllocBoard();
  InitPlayer(player);
  InitPlayerPosition(player);

  InitBoard(board);

  SetPlayerBlockType(player, kBlockT);
  SetPlayerBoardBlock(player->board_, kBlockT, kDirectionFirst);
  MovePlayerRight(player);
  MovePlayerRight(player);
  MovePlayerRight(player);

  bool flag = CheckFutureCollideWithDown(player, board);
  ASSERT_EQ(flag, false);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  flag = CheckFutureCollideWithDown(player, board);
  ASSERT_EQ(flag, false);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  flag = CheckFutureCollideWithDown(player, board);
  ASSERT_EQ(flag, false);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  flag = CheckFutureCollideWithDown(player, board);
  ASSERT_EQ(flag, false);
  MovePlayerDown(player);
  MovePlayerDown(player);
  MovePlayerDown(player);
  flag = CheckFutureCollideWithDown(player, board);
  ASSERT_EQ(flag, true);
}

TEST_F(ModelTest, InitGameStatusTest) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);
}

TEST_F(ModelTest, AddScoreGameStatusTest1) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);

  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 100);
  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 200);
  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 300);
  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 400);
  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 500);
}

TEST_F(ModelTest, AddScoreGameStatusTest2) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);

  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 100);
  AddScoreGameStatus(&game_status, 2);
  ASSERT_EQ(game_status.score_, 400);
  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 500);
  AddScoreGameStatus(&game_status, 2);
  ASSERT_EQ(game_status.score_, 800);
  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 900);
}

TEST_F(ModelTest, AddScoreGameStatusTest3) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);

  AddScoreGameStatus(&game_status, 1);
  ASSERT_EQ(game_status.score_, 100);
  AddScoreGameStatus(&game_status, 2);
  ASSERT_EQ(game_status.score_, 400);
  AddScoreGameStatus(&game_status, 3);
  ASSERT_EQ(game_status.score_, 1100);
  AddScoreGameStatus(&game_status, 4);
  ASSERT_EQ(game_status.score_, 2600);
  AddScoreGameStatus(&game_status, 5);
  ASSERT_EQ(game_status.score_, 4100);
}
TEST_F(ModelTest, AddScoreGameStatusUpdateGameStatusLevelTest1) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);

  AddScoreGameStatus(&game_status, 1);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 100);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, 2);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 400);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, 1);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 500);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, 2);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 800);
  ASSERT_EQ(game_status.level_, 1);
  AddScoreGameStatus(&game_status, 1);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 900);
  ASSERT_EQ(game_status.level_, 1);
}

TEST_F(ModelTest, AddScoreGameStatusUpdateGameStatusLevelTest2) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);

  AddScoreGameStatus(&game_status, 1);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 100);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, 2);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 400);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, 3);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 1100);
  ASSERT_EQ(game_status.level_, 1);
  AddScoreGameStatus(&game_status, 4);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 2600);
  ASSERT_EQ(game_status.level_, 4);
  AddScoreGameStatus(&game_status, 5);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 4100);
  ASSERT_EQ(game_status.level_, 6);
}

TEST_F(ModelTest, AddScoreGameStatusNoChangesTest) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);

  AddScoreGameStatus(&game_status, 0);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, 0);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, 0);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, 0);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);
}

TEST_F(ModelTest, AddScoreGameStatusInvalidArgumentTest) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);

  AddScoreGameStatus(&game_status, -1);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);
  AddScoreGameStatus(&game_status, -100);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);
}

TEST_F(ModelTest, AddScoreGameStatusUpdateGameStatusLevelMaxLevelExceedTest) {
  GameStatus game_status{};
  InitGameStatus(&game_status);
  ASSERT_EQ(game_status.score_, 0);
  ASSERT_EQ(game_status.level_, 0);

  AddScoreGameStatus(&game_status, 4);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 1500);
  ASSERT_EQ(game_status.level_, 2);

  AddScoreGameStatus(&game_status, 4);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 3000);
  ASSERT_EQ(game_status.level_, 5);

  AddScoreGameStatus(&game_status, 4);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 4500);
  ASSERT_EQ(game_status.level_, 7);

  AddScoreGameStatus(&game_status, 4);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 6000);
  ASSERT_EQ(game_status.level_, 10);

  AddScoreGameStatus(&game_status, 4);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 7500);
  ASSERT_EQ(game_status.level_, 10);

  AddScoreGameStatus(&game_status, 4);
  UpdateGameStatusLevel(&game_status);
  ASSERT_EQ(game_status.score_, 9000);
  ASSERT_EQ(game_status.level_, 10);
}

TEST_F(ModelTest, SetPlayerBoardBlockTestIFirstRotation) {
  PlayerBoard *player_board = AllocPlayerBoard();
  SetPlayerBoardBlock(player_board, kBlockI, kDirectionFirst);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (j == 1) {
        ASSERT_EQ(player_board->board_[i][j].is_set_, true);
      } else {
        ASSERT_EQ(player_board->board_[i][j].is_set_, false);
      }
    }
  }
}

TEST_F(ModelTest, SetPlayerBoardBlockTestISecondRotation) {
  PlayerBoard *player_board = AllocPlayerBoard();
  SetPlayerBoardBlock(player_board, kBlockI, kDirectionSecond);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (i == 2) {
        ASSERT_EQ(player_board->board_[i][j].is_set_, true);
      } else {
        ASSERT_EQ(player_board->board_[i][j].is_set_, false);
      }
    }
  }
}

TEST_F(ModelTest, SetPlayerBoardBlockTestIThirdRotation) {
  PlayerBoard *player_board = AllocPlayerBoard();
  SetPlayerBoardBlock(player_board, kBlockI, kDirectionThird);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (j == 1) {
        ASSERT_EQ(player_board->board_[i][j].is_set_, true);
      } else {
        ASSERT_EQ(player_board->board_[i][j].is_set_, false);
      }
    }
  }
}

TEST_F(ModelTest, SetPlayerBoardBlockTestIForthRotation) {
  PlayerBoard *player_board = AllocPlayerBoard();
  SetPlayerBoardBlock(player_board, kBlockI, kDirectionForth);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      if (i == 2) {
        ASSERT_EQ(player_board->board_[i][j].is_set_, true);
      } else {
        ASSERT_EQ(player_board->board_[i][j].is_set_, false);
      }
    }
  }
}

TEST_F(ModelTest, InitPlayerBoardTest) {
  PlayerBoard *player_board = AllocPlayerBoard();
  InitPlayerBoard(player_board);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ASSERT_EQ(player_board->board_[i][j].color_, COLOR_BLACK);
      ASSERT_EQ(player_board->board_[i][j].is_set_, false);
    }
  }
}
TEST_F(ModelTest, CopyPlayerBoardTest) {
  PlayerBoard *player_board_1 = AllocPlayerBoard();
  PlayerBoard *player_board_2 = AllocPlayerBoard();
  InitPlayerBoard(player_board_1);
  InitPlayerBoard(player_board_2);

  for (int i = 0; i < PLAYER_BOARD_SIZE; i += 2) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; j += 2) {
      player_board_1->board_[i][j].is_set_ = true;
    }
  }
  CopyPlayerBoard(player_board_2, player_board_1);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ASSERT_EQ(player_board_1->board_[i][j].is_set_,
                player_board_2->board_[i][j].is_set_);
      ASSERT_EQ(player_board_1->board_[i][j].color_,
                player_board_2->board_[i][j].color_);
    }
  }
}

TEST_F(ModelTest, InitPlayerTest) {
  Player *player = AllocPlayer();
  InitPlayer(player);
  ASSERT_EQ(player->x_, 0);
  ASSERT_EQ(player->y_, 0);
  ASSERT_GE(player->block_type_, 0);
  ASSERT_GE(player->direction_, 0);
}
TEST_F(ModelTest, InitNextPlayerTest) {
  Player *player = AllocPlayer();
  InitNextPlayer(player);
  ASSERT_EQ(player->x_, INIT_NEXT_PLAYER_POS_X);
  ASSERT_EQ(player->y_, INIT_NEXT_PLAYER_POS_Y);
  ASSERT_GE(player->block_type_, 0);
  ASSERT_GE(player->direction_, 0);
}
TEST_F(ModelTest, InitPlayerPositionTest) {
  Player *player = AllocPlayer();
  InitPlayerPosition(player);
  ASSERT_EQ(player->x_, INIT_PLAYER_POS_X);
  ASSERT_EQ(player->y_, INIT_PLAYER_POS_Y);
  ASSERT_GE(player->block_type_, 0);
  ASSERT_GE(player->direction_, 0);
}
TEST_F(ModelTest, CopyPlayerTest) {
  Player *player = AllocPlayer();
  InitNextPlayer(player);
  Player *player_2 = AllocPlayer();
  CopyPlayer(player_2, player);

  ASSERT_EQ(player_2->x_, player->x_);
  ASSERT_EQ(player_2->y_, player->y_);
  ASSERT_EQ(player_2->block_type_, player->block_type_);
  ASSERT_EQ(player_2->direction_, player->direction_);
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ASSERT_EQ(player->board_->board_[i][j].color_,
                player->board_->board_[i][j].color_);
      ASSERT_EQ(player->board_->board_[i][j].is_set_,
                player->board_->board_[i][j].is_set_);
    }
  }
}
TEST_F(ModelTest, SetPlayerBlockRotationTest) {
  Player *player = AllocPlayer();
  InitPlayer(player);
  SetPlayerBlockRotation(player, kDirectionThird);
  ASSERT_EQ(player->direction_, kDirectionThird);
}
TEST_F(ModelTest, SetPlayerNextBlockRotationTest) {
  Player *player = AllocPlayer();
  InitPlayer(player);
  SetPlayerBlockRotation(player, kDirectionFirst);
  SetPlayerNextBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionSecond);
  SetPlayerNextBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionThird);
  SetPlayerNextBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionForth);
  SetPlayerNextBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionFirst);
}
TEST_F(ModelTest, SetPlayerPreviousBlockRotationTest) {
  Player *player = AllocPlayer();
  InitPlayer(player);
  SetPlayerBlockRotation(player, kDirectionFirst);
  SetPlayerPreviousBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionForth);
  SetPlayerPreviousBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionThird);
  SetPlayerPreviousBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionSecond);
  SetPlayerPreviousBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionFirst);
  SetPlayerPreviousBlockRotation(player);
  ASSERT_EQ(player->direction_, kDirectionForth);
}
TEST_F(ModelTest, MovePlayerRightTest1) {
  Player *player = AllocPlayer();
  Player *player_before = AllocPlayer();
  InitPlayer(player);
  InitPlayer(player_before);
  InitPlayerPosition(player);
  InitPlayerPosition(player_before);

  MovePlayerRight(player);

  ASSERT_EQ(player->x_, player_before->x_ + 1);
  ASSERT_EQ(player->y_, player_before->y_);
}
TEST_F(ModelTest, MovePlayerRightTest2) {
  Player *player = AllocPlayer();
  Player *player_before = AllocPlayer();
  InitPlayer(player);
  InitPlayerPosition(player);
  CopyPlayer(player_before, player);

  MovePlayerRight(player);
  MovePlayerRight(player);
  MovePlayerRight(player);
  ASSERT_EQ(player->x_, player_before->x_ + 3);
  ASSERT_EQ(player->y_, player_before->y_);
}
TEST_F(ModelTest, MovePlayerLeftRightTest) {
  Player *player = AllocPlayer();
  Player *player_before = AllocPlayer();
  InitPlayer(player);
  InitPlayerPosition(player);

  CopyPlayer(player_before, player);

  MovePlayerRight(player);
  MovePlayerLeft(player);

  ASSERT_EQ(player_before->x_, player->x_);
  ASSERT_EQ(player_before->y_, player->y_);
  ASSERT_EQ(player_before->block_type_, player->block_type_);
  ASSERT_EQ(player_before->direction_, player->direction_);
  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ASSERT_EQ(player->board_->board_[i][j].color_,
                player_before->board_->board_[i][j].color_);
      ASSERT_EQ(player->board_->board_[i][j].is_set_,
                player_before->board_->board_[i][j].is_set_);
    }
  }
}
TEST_F(ModelTest, MovePlayerUpTest) {
  Player *player = AllocPlayer();
  Player *player_before = AllocPlayer();
  InitPlayer(player);
  InitPlayer(player_before);
  CopyPlayer(player_before, player);

  MovePlayerUp(player);

  ASSERT_EQ(player_before->x_, player->x_);
  ASSERT_EQ(player_before->y_, player->y_ + 1);
  ASSERT_EQ(player_before->block_type_, player->block_type_);
  ASSERT_EQ(player_before->direction_, player->direction_);
}
TEST_F(ModelTest, MovePlayerUpDownTest) {
  Player *player = AllocPlayer();
  Player *player_before = AllocPlayer();
  InitPlayer(player);
  InitPlayerPosition(player);
  CopyPlayer(player_before, player);

  MovePlayerUp(player);
  MovePlayerDown(player);

  ASSERT_EQ(player_before->x_, player->x_);
  ASSERT_EQ(player_before->y_, player->y_);
  ASSERT_EQ(player_before->block_type_, player->block_type_);
  ASSERT_EQ(player_before->direction_, player->direction_);

  for (int i = 0; i < PLAYER_BOARD_SIZE; ++i) {
    for (int j = 0; j < PLAYER_BOARD_SIZE; ++j) {
      ASSERT_EQ(player->board_->board_[i][j].color_,
                player_before->board_->board_[i][j].color_);
      ASSERT_EQ(player->board_->board_[i][j].is_set_,
                player_before->board_->board_[i][j].is_set_);
    }
  }
}

TEST_F(ModelTest, RecordsAddSaveLoadTest1) {
  Records *records = AllocRecords();
  Records *records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii1", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii2", 600, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii3", 700, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii4", 800, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii5", 900, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii6", 1000, TETRIS_RECORDS_FILE_NAME);

  SaveRecords(records, TETRIS_RECORDS_FILE_NAME);
  LoadRecords(records2, TETRIS_RECORDS_FILE_NAME);
  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    ASSERT_EQ(records->records_[i].is_current_player_,
              records2->records_[i].is_current_player_);
    ASSERT_EQ(records->records_[i].score_, records2->records_[i].score_);
    ASSERT_STREQ(records->records_[i].name_, records2->records_[i].name_);
  }
}

TEST_F(ModelTest, RecordsAddSaveLoadTest2) {
  Records *records = AllocRecords();
  Records *records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 600, TETRIS_RECORDS_FILE_NAME);

  SaveRecords(records, TETRIS_RECORDS_FILE_NAME);
  LoadRecords(records2, TETRIS_RECORDS_FILE_NAME);
  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    ASSERT_EQ(records->records_[i].is_current_player_,
              records2->records_[i].is_current_player_);
    ASSERT_EQ(records->records_[i].score_, records2->records_[i].score_);
    ASSERT_STREQ(records->records_[i].name_, records2->records_[i].name_);
  }
}

TEST_F(ModelTest, RecordsAddSaveLoadTest3) {
  Records *records = AllocRecords();
  Records *records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 600, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 500, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii", 600, TETRIS_RECORDS_FILE_NAME);
  RemoveRecord(records, "Arsenii", TETRIS_RECORDS_FILE_NAME);

  for (int i = 0; i < RECORDS_NUMBER; ++i) {
    ASSERT_EQ(records->records_[i].score_, 0);
    ASSERT_STREQ(records->records_[i].name_, "");
  }
}
TEST_F(ModelTest, RecordsAddSaveLoadTest4) {
  Records *records = AllocRecords();
  Records *records2 = AllocRecords();
  InitRecords(records);
  InitRecords(records2);

  AddRecord(records, "Arsenii8", 1200, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii7", 1100, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii6", 1000, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii5", 900, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii4", 800, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii3", 700, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii2", 600, TETRIS_RECORDS_FILE_NAME);
  AddRecord(records, "Arsenii1", 500, TETRIS_RECORDS_FILE_NAME);

  ASSERT_EQ(records->records_[0].score_, 1200);
  ASSERT_STREQ(records->records_[0].name_, "Arsenii8");
}

TEST_F(ModelTest, EatFruitTest) {
  signal_type = kSignalEnterButton;

  ControllerSnake(signal_type, parameters);

  signal_type = kSignalMoveDown;
  ControllerSnake(signal_type, parameters);

  parameters->s_fruit_->x_ = (parameters->s_player_->snake_body_[0].x_);
  parameters->s_fruit_->y_ = (parameters->s_player_->snake_body_[0].y_ + 1);

  for (int i = 0; i < 25; ++i) {
    signal_type = kSignalMoveDown;
    ControllerSnake(signal_type, parameters);
  }

  ASSERT_EQ(*parameters->s_state_, kGameOver);
}

TEST_F(ModelTest, CollideWithItself) {
  signal_type = kSignalEnterButton;

  ControllerSnake(signal_type, parameters);
  parameters->s_player_->snake_length_ = 10;

  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveDown;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveLeft;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveUp;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveRight;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalMoveDown;
  ControllerSnake(signal_type, parameters);

  ASSERT_EQ(*parameters->s_state_, kGameOver);
}

TEST_F(ModelTest, MoveStraightTest) {
  signal_type = kSignalEnterButton;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  sleep(1);
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  sleep(1);
  signal_type = kSignalNone;
  ControllerSnake(signal_type, parameters);
  signal_type = kSignalNone;

  ASSERT_EQ(*parameters->s_state_, kGameOver);
}

} // namespace s21
