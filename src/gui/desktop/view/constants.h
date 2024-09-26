#ifndef CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_CONSTANTS_H_
#define CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_CONSTANTS_H_

#include <QColor>

namespace s21 {
namespace constants {
inline constexpr int kCellSize = 21;
inline constexpr int kRows = 20;
inline constexpr int kColumns = 10;

inline static QColor kColorArray[] = {
    {254, 3, 0, 210},     {255, 102, 0, 210},   {255, 254, 6, 210},
    {255, 153, 203, 210}, {1, 128, 2, 210},     {1, 0, 254, 210},
    {129, 0, 128, 210},   {150, 150, 150, 100},
};

}  // namespace constants

enum class CurrentGame {
  kTetris = 0,
  kSnake = 1,
  kCarRacing = 2,
  kTankClassic = 3,
};

}  // namespace s21

#endif  // CPP3_BRICK_GAME_V_2_0_1_GUI_DESKTOP_VIEW_CONSTANTS_H_
