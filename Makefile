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
 				src/brick_game/common/fsm_types.c
TETRIS_SRC := 	src/brick_game/tetris/fsm/fsm_matrix.c
BACKEND_CXX:=	src/brick_game/snake/controller/controller.cc \
				src/brick_game/snake/model/model.cc \
				src/brick_game/snake/action/action.cc \
				src/brick_game/snake/move_snake/move_snake.cc
FRONTEND:=		src/gui/cli/frontend.c \
				src/gui/cli/cjson.c \
				src/gui/cli/draw_objects.c \
				src/gui/cli/get_player_name.c \
				src/gui/cli/retrieve_data.c


SOURCES_FOR_TESTS:= tests/tetris/main_test.c


SHARED_LIB_NAME := libbrickgame.so


ifeq ($(OS_NAME), GNU/Linux)
    OPEN_COMMAND := xdg-open
#	APP_DESTINATION:=../build
endif



DESKTOP_SOURCES := src/gui/desktop/view
DESKTOP_BUILD := build_desktop
APP_DESTINATION:=	build_desktop/brickgame_desktop.app/Contents/MacOS

OPEN_COMMAND =open
# if Fedora, need to uncomment followed two lines
#OPEN_COMMAND=xdg-open
#APP_DESTINATION:=build_desktop


# Create .so file from all backend and common sources
${SHARED_LIB_NAME}: ${TETRIS_SRC} ${BACKEND} ${BACKEND_CXX} ${COMMON}
	$(CXX) -g $^ -shared -fPIC -o $(SHARED_LIB_NAME)

# IMPORTANT!! For Linux you need to add library manually
add_library_to_path:
	$(echo "export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH") >> zshrc.txt


fix_docker:
	sed -ie 's/credsStore/credStore/g' ~/.docker/config.json

run_postgres:
	cd docker && docker-compose up -d

server:
	cd src/brick_game/server && go build -o server.out && ./server.out

lib: ${SHARED_LIB_NAME}

all: install run_cli

install: uninstall install_cli install_desktop

uninstall:
	@rm -f brickgame_cli.out
	@rm -rf ${DESKTOP_BUILD}
	@echo "Uninstallation is finished"

run_web_ui:
	open http://localhost:8080/static/tetris.html

install_cli: ${SHARED_LIB_NAME} ${FRONTEND}
	$(CXX) $(LIBRARIES) $^ -L. -lcurl \
	src/brick_game/common/common/color_handler.c \
	-lbrickgame -o brickgame_cli.out

#install_cli: ${BACKEND} ${BACKEND_CXX} ${COMMON} ${TETRIS} ${FRONTEND}
#	$(CXX) $(LIBRARIES) $^ \
#	brick_game/common/common/color_handler.c \
#	-o brickgame_cli.out

install_desktop:
	cmake -DCMAKE_BUILD_TYPE=Release -S ${DESKTOP_SOURCES} -B ${DESKTOP_BUILD}
	cmake --build ${DESKTOP_BUILD} --target brickgame_desktop -j 4

run_cli:
	./brickgame_cli.out
run_desktop:
	${APP_DESTINATION}/brickgame_desktop

dvi:
	${OPEN_COMMAND} ../dvi/README.html


test: test_tetris test_snake

test_tetris: ${SHARED_LIB_NAME}
	@${CXX} ${SOURCES_FOR_TESTS} ${SHARED_LIB_NAME} -lcheck -lm  -o test.out
	@./test.out
	@#make clean

TEST_SNAKE_SRC := tests/snake
TEST_SNAKE_DEST := tests/snake/build
TEST_SNAKE_TARGET := tests

test_snake:
	cmake -DCMAKE_BUILD_TYPE=Release -S ${TEST_SNAKE_SRC} -B ${TEST_SNAKE_DEST}
	cmake --build ${TEST_SNAKE_DEST} --target tests -j 8
	./${TEST_SNAKE_DEST}/tests

test_valgrind:
	@${CC} ${CXXFLAGS} ${CXXCOV} $(SOURCES_FOR_TESTS) -lgtest -lstdc++ -lm  -o test.out
	@valgrind ${VALGRIND_FLAGS} ./test.out

style_check:
	@cp ../materials/linters/.clang-format .
	@find .. -type f -name "*.cc" -exec clang-format -n {} \;
	@find .. -type f -name "*.c" -exec clang-format -n {} \;
	@find .. -type f -name "*.h" -exec clang-format -n {} \;
	@rm .clang-format
	@echo "Clang format style check is finished"
style:
	@cp ../materials/linters/.clang-format .
	@find .. -type f -name "*.cc" -exec clang-format -i {} \;
	@find .. -type f -name "*.c" -exec clang-format -i {} \;
	@find .. -type f -name "*.h" -exec clang-format -i {} \;
	@rm .clang-format
	@echo "Clang format style apply is finished"

clean: clean_project clean_static_lib clean_log clean_exec clean_obj clean_gcov clean_lcov clean_lcov_report clean_dist clean_dynamic_libs
	@echo "Clean finished"

clean_project:
	@rm -rf ${APP_DESTINATION}
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

