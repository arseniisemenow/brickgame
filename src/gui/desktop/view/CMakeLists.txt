cmake_minimum_required(VERSION 3.5)

project(brickgame_desktop VERSION 0.1)

# Enable C and C++ languages
enable_language(C)
enable_language(CXX)

# Use current directories for includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable automatic UI, MOC, and RCC processing for Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and link Qt Widgets
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Include directories
include_directories(../../../)
include_directories(.)

# Source files for the library
set(PROJECT_SOURCES
        ../../../brick_game/common/block/block.c
        ../../../brick_game/common/board/board.c
        ../../../brick_game/common/cell/cell.c
        ../../../brick_game/common/collisions_checker/collisions_checker.c
        ../../../brick_game/common/game_status/game_status.c
        ../../../brick_game/common/parameters/parameters.c
        ../../../brick_game/common/player/player.c
        ../../../brick_game/common/player/player_board/player_board.c
        ../../../brick_game/common/records/records.c
        ../../../brick_game/common/time_handler/time_handler.c
        ../../../brick_game/tetris/fsm/fsm_matrix.c
        ../../../brick_game/tetris/backend/backend.c
        ../../../brick_game/snake/controller/controller.cc
        ../../../brick_game/snake/model/model.cc
        ../../../brick_game/snake/action/action.cc
        ../../../brick_game/snake/move_snake/move_snake.cc
        main.cc
        view.cc
        view.h
        view.ui
        grid_widget/grid_widget.cc
        grid_widget/grid_widget.h
        view_tab_switcher/view_tab_switcher.cc
        view_tab_switcher/view_tab_switcher.h
        style_handler/style_handler.cc
        next_player_grid_widget/next_player_grid_widget.cc
        constants.h
        ../../../brick_game/common/fsm_types.c
)

# Create a shared library instead of an executable
add_library(brickgame_desktop SHARED ${PROJECT_SOURCES})

# Link the library with Qt
target_link_libraries(brickgame_desktop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Set target properties for the shared library
set_target_properties(brickgame_desktop PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)

# On macOS, set additional bundle properties
if(APPLE)
    set_target_properties(brickgame_desktop PROPERTIES
            MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
            MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
            MACOSX_BUNDLE TRUE
    )
endif()

# If building with Qt6, finalize the library
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(brickgame_desktop)
endif()
