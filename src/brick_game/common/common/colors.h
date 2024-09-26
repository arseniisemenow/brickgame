#ifndef CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_COLORS_H_
#define CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_COLORS_H_

#ifndef COLOR_BLACK
#define COLOR_BLACK (0)
#endif  // COLOR_BLACK

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  kBlockColorI = 0,
  kBlockColorJ = 1,
  kBlockColorL = 2,
  kBlockColorO = 3,
  kBlockColorS = 4,
  kBlockColorT = 5,
  kBlockColorZ = 6,
  kBlockColorPredict = 7,
} BlockColorType;

/** Set colors for corresponding block type.
 * Setting by index
 **/
static const BlockColorType kBlockColors[] = {
    kBlockColorI, kBlockColorJ, kBlockColorL, kBlockColorO,
    kBlockColorS, kBlockColorT, kBlockColorZ, kBlockColorPredict};
#ifdef __cplusplus
}
#endif

#endif  // CPP3_BRICK_GAME_V_2_0_1_BRICK_GAME_COMMON_COMMON_COLORS_H_
