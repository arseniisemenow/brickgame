#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_FSM_TYPES_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_FSM_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  kStart = 0,
  kSpawn = 1,
  kMoving = 2,
  kCollide = 3,
  kGameOver = 4,
  kExitState = 5,
  kPause = 6,
} State;

typedef enum {
  kSignalNone = 0,
  kSignalMoveUp = 1,
  kSignalMoveDown = 2,
  kSignalMoveLeft = 3,
  kSignalMoveRight = 4,
  kSignalEscapeButton = 5,
  kSignalEnterButton = 6,
  kSignalPauseButton = 7,
} SignalType;
#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_FSM_TYPES_H_
