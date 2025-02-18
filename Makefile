CC = gcc
CXX = g++
CFLAGS = -Werror -Wall -Wextra
CXXFLAGS = -Werror -Wall -Wextra -std=c++17
LDFLAGS =
LIBRARIES = -lncurses
TEST_FLAGS      := -lcheck -lm -lpthread
GCOV_FLAGS      := -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log
CXXCOV 			:=  --coverage

DIST_DIR :=archive

DEBUGGER := 	src/brick_game/tetris/debugger/debugger.c
BACKEND := 		src/brick_game/tetris/backend/backend.c
COMMON :=   	src/brick_game/common/common/colors.c \
				src/brick_game/common/block/block.c \
				src/brick_game/common/cell/cell.c \
				src/brick_game/common/collisions_checker/collisions_checker.c \
				src/brick_game/common/parameters/parameters.c \
				src/brick_game/common/game_status/game_status.c \
				src/brick_game/common/board/board.c \
				src/brick_game/common/player/player.c \
				src/brick_game/common/records/records.c \
				src/brick_game/common/player/player_board/player_board.c \
 				src/brick_game/common/time_handler/time_handler.c \
 				src/brick_game/common/api_client/api_client.c \
 				src/brick_game/common/cjson/cjson.c \
 				src/brick_game/common/fsm_types.c
TETRIS_SRC := 	src/brick_game/tetris/fsm/fsm_matrix.c
BACKEND_CXX:=	src/brick_game/snake/controller/controller.cc \
				src/brick_game/snake/model/model.cc \
				src/brick_game/snake/action/action.cc \
				src/brick_game/snake/move_snake/move_snake.cc
FRONTEND:=		src/gui/cli/frontend.c \
				src/gui/cli/draw_objects.c \
				src/gui/cli/get_player_name.c \
				src/gui/cli/tetris_loop.c \
				src/gui/cli/snake_loop.c \
				src/gui/cli/car_racing_loop.c


SOURCES_FOR_TESTS:= tests/tetris/main_test.c


SHARED_LIB_NAME := libbrickgame.so

OS_NAME	 := $(shell uname 2>/dev/null || echo "Unknown")

OPEN_COMMAND := open

ifeq ($(OS_NAME), Linux)
    OPEN_COMMAND := xdg-open
endif

DESKTOP_SOURCES := src/gui/desktop/view
DESKTOP_BUILD := build_desktop
CLI_BUILD := build_cli
APP_DESTINATION:=	build_desktop/brickgame_desktop.app/Contents/MacOS

# Create .so file from all backend and common sources
${SHARED_LIB_NAME}: ${TETRIS_SRC} ${BACKEND} ${BACKEND_CXX} ${COMMON}
	@mkdir -p build
	$(CXX) -g $^ -shared -fPIC -lcurl -o build/$(SHARED_LIB_NAME)

# IMPORTANT!! For Linux you need to add library manually
add_library_to_path:
	$(echo "export LD_LIBRARY_PATH=$(pwd)/build:$LD_LIBRARY_PATH") >> zshrc.txt

fix_docker:
	sed -ie 's/credsStore/credStore/g' ~/.docker/config.json

run_postgres:
	cd docker && docker-compose up -d

server: run_postgres
	cd src/brick_game/server && go build -o build/server.out && ./build/server.out &
server-stop:
	@pid=$$(ps aux | grep './build/server.out' | grep -v grep | awk '{print $$2}'); \
    if [ -n "$$pid" ]; then \
        echo "Killing server with PID: $$pid"; \
        kill $$pid; \
    else \
        echo "Server process not found."; \
    fi

lib: ${SHARED_LIB_NAME}

all: install run_cli

install: uninstall install_cli install_desktop
	-make server

uninstall:
	@rm -rf build
	@make server-stop
	@echo "Uninstallation is finished"

run_web:
	open http://localhost:8080/static/tetris.html

install_cli: ${SHARED_LIB_NAME}
	mkdir -p build
	mkdir -p build/${CLI_BUILD}
	$(CXX) $(LIBRARIES) ${FRONTEND} build/${SHARED_LIB_NAME} -lcurl \
	src/brick_game/common/common/color_handler.c \
	-o build/${CLI_BUILD}/brickgame_cli.out

install_desktop:
	cmake -DCMAKE_BUILD_TYPE=Release -S ${DESKTOP_SOURCES} -B build/${DESKTOP_BUILD}
	cmake --build build/${DESKTOP_BUILD} --target brickgame_desktop -j 4

run_cli:
	./build/${CLI_BUILD}/brickgame_cli.out
run_desktop:
	./build/${DESKTOP_BUILD}/brickgame_desktop
dvi:
	${OPEN_COMMAND} dvi-folder/README.html

test: test_tetris test_snake test_race

TEST_TETRIS_DEST := build/tests/tetris
TEST_SNAKE_DEST := build/tests/snake
TEST_SNAKE_SRC := tests/snake
TEST_SNAKE_TARGET := tests
test_tetris: ${SHARED_LIB_NAME}
	@mkdir -p build/tests/tetris
	@${CXX} ${SOURCES_FOR_TESTS} build/${SHARED_LIB_NAME} -lcheck -lm -o ./${TEST_TETRIS_DEST}/tests.out
	@./${TEST_TETRIS_DEST}/tests.out
test_tetris_valgrind: ${SHARED_LIB_NAME}
	@mkdir -p build/tests/tetris
	@${CXX} ${SOURCES_FOR_TESTS} build/${SHARED_LIB_NAME} -lcheck -lm -o ./${TEST_TETRIS_DEST}/tests.out
	@./${TEST_TETRIS_DEST}/tests.out
	@valgrind ${VALGRIND_FLAGS} ./${TEST_TETRIS_DEST}/tests.out

test_snake:
	cmake -DCMAKE_BUILD_TYPE=Release -S ${TEST_SNAKE_SRC} -B ${TEST_SNAKE_DEST}
	cmake --build ${TEST_SNAKE_DEST} --target tests -j 8
	./${TEST_SNAKE_DEST}/tests
test_snake_valgrind:
	cmake -DCMAKE_BUILD_TYPE=Release -S ${TEST_SNAKE_SRC} -B ${TEST_SNAKE_DEST}
	cmake --build ${TEST_SNAKE_DEST} --target tests -j 8
	@valgrind ${VALGRIND_FLAGS} ./${TEST_SNAKE_DEST}/tests.out

test_race:
	cd src/brick_game/race && go test -v

coverage_race:
	cd src/brick_game/race && go test -cover ./...

test_valgrind:
	@${CC} ${CXXFLAGS} ${CXXCOV} $(SOURCES_FOR_TESTS) -lgtest -lstdc++ -lm  -o test.out
	@valgrind ${VALGRIND_FLAGS} ./test.out



clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist clean_dynamic_libs
	@echo "Clean finished"

clean_project:
	@rm -rf ${APP_DESTINATION}
	@rm -rf ${DESKTOP_BUILD}
	@rm -rf ${CLI_BUILD}
	@rm -rf build
clean_dist:
	@cd . && rm -rf archive
	@cd . && rm -rf archive.tar.gz
clean_after_building:
	@rm -rf ${OBJ_DIR}
clean_static_lib:
	@find . -type f -name "*.a" -exec rm {} \;
clean_log:
	@find . -type f -name "*.log" -exec rm {} \;
clean_exec:
	@find . -type f -name "*.out" -exec rm {} \;
clean_obj:
	@find . -type f -name "*.o" -exec rm {} \;
clean_gcov:
	@find . -type f -name "*.gcda" -exec rm {} \;
	@find . -type f -name "*.gcno" -exec rm {} \;
clean_lcov:
	@find . -type f -name "*.info" -exec rm {} \;
clean_lcov_report:
	@rm -rf report
clean_dynamic_libs:
	@find . -type f -name "*.so" -exec rm {} \;

dist: clean_dist
	cd ../ && mkdir -p ${DIST_DIR}
	cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
	cd ../ && cp -rf src/gui ${DIST_DIR}/gui
	cd ../ && cp -rf src/Makefile ${DIST_DIR}/
	cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	cd ../ && rm -rf ${DIST_DIR}
dist_unpack:
	cd ../ && tar -xzvf archive.tar.gz

FIND_EXTENSIONS_CC := -name "*.cc"
FIND_EXTENSIONS_C := -name "*.c"
FIND_EXTENSIONS_H := -name "*.h"
FIND_EXTENSIONS_HPP := -name "*.hpp"
FIND_EXTENSIONS_CPP := -name "*.cpp"
FIND_FLAG_FOR_MATCHES := \( ${FIND_EXTENSIONS_CC} -o ${FIND_EXTENSIONS_C} -o ${FIND_EXTENSIONS_H} -o ${FIND_EXTENSIONS_HPP} -o ${FIND_EXTENSIONS_CPP} \)
FIND_DIR := .
CLANG_STYLE := --style=google
CLANG_COMMAND_HIGHLIGHT := clang-format ${CLANG_STYLE} -n
CLANG_COMMAND_FIX :=  clang-format ${CLANG_STYLE} -i
FIND_FLAGS_HIGHLIGHT := -type f ${FIND_FLAG_FOR_MATCHES} -exec ${CLANG_COMMAND_HIGHLIGHT} {} \;
FIND_FLAGS_FIX := -type f ${FIND_FLAG_FOR_MATCHES} -exec ${CLANG_COMMAND_FIX} {} \;
FIND_HIGHLIGHT := find ${FIND_DIR} ${FIND_FLAGS_HIGHLIGHT}
FIND_FIX := find ${FIND_DIR} ${FIND_FLAGS_FIX}
style_check:
	@${FIND_HIGHLIGHT}
	@echo "Clang format style check is finished"
style:
	@${FIND_FIX}
	@echo "Clang format style apply is finished"
