cmake_minimum_required(VERSION 3.5)

project(manual_tests VERSION 0.1)

enable_language(C)
enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../src)
include_directories(.)

add_executable(manual_tests
        ../../src/brick_game/common/block/block.c
        ../../src/brick_game/common/board/board.c
        ../../src/brick_game/common/cell/cell.c
        ../../src/brick_game/common/collisions_checker/collisions_checker.c
        ../../src/brick_game/common/game_status/game_status.c
        ../../src/brick_game/common/parameters/parameters.c
        ../../src/brick_game/common/player/player.c
        ../../src/brick_game/common/player/player_board/player_board.c
        ../../src/brick_game/common/records/records.c
        ../../src/brick_game/common/time_handler/time_handler.c
        ../../src/brick_game/tetris/fsm/fsm_matrix.c
        ../../src/brick_game/tetris/backend/backend.c
        ../../src/brick_game/snake/controller/controller.cc
        ../../src/brick_game/snake/model/model.cc
        ../../src/brick_game/snake/action/action.cc
        ../../src/brick_game/snake/move_snake/move_snake.cc
        ../../src/brick_game/common/fsm_types.c
#        ../../src/common/constants.h
        manual_tests.c
)
