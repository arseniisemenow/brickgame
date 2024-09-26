#include "block.h"

#include <stdlib.h>

BlockType GetRandomBlockType() {
  BlockType block_type = (BlockType)(rand() % (kBlockZ + 1));
  return block_type;
}

Direction GetNextBlockRotation(Direction block_rotation) {
  Direction next_block_rotation = kDirectionFirst;
  if (block_rotation == kDirectionFirst) {
    next_block_rotation = kDirectionSecond;
  } else if (block_rotation == kDirectionSecond) {
    next_block_rotation = kDirectionThird;
  } else if (block_rotation == kDirectionThird) {
    next_block_rotation = kDirectionForth;
  } else if (block_rotation == kDirectionForth) {
    next_block_rotation = kDirectionFirst;
  }
  return next_block_rotation;
}

Direction GetPreviousBlockRotation(Direction block_rotation) {
  Direction previous_block_rotation = kDirectionFirst;
  if (block_rotation == kDirectionFirst) {
    previous_block_rotation = kDirectionForth;
  } else if (block_rotation == kDirectionSecond) {
    previous_block_rotation = kDirectionFirst;
  } else if (block_rotation == kDirectionThird) {
    previous_block_rotation = kDirectionSecond;
  } else if (block_rotation == kDirectionForth) {
    previous_block_rotation = kDirectionThird;
  }
  return previous_block_rotation;
}

BlockColorType GetBlockColor(BlockType block_type) {
  BlockColorType block_color_type;
  block_color_type = kBlockColors[block_type];
  return block_color_type;
}