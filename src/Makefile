SRC_DIR := src
TETRIS_DIR := brick_game/tetris
TESTS_DIR := unit_tests
GUI_DIR := gui/cli
OBJ_DIR := obj
BIN_DIR := bin
MAIN := $(TETRIS_DIR)/main.c
CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11 -fprofile-arcs -ftest-coverage
LDFLAGS := -lncurses
MKDIR_P := mkdir -p
SOURCES := $(wildcard $(TETRIS_DIR)/*.c $(GUI_DIR)/*.c)
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all clean install uninstall dvi dist test gcov_report style_fix style leaks valgrind_tetris rebuild run

OS = $(shell uname)

ifeq ($(OS), Linux)
	TEST_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
	OPEN = xdg-open
	VALGRIND_CMD = valgrind --tool=memcheck --leak-check=full
else
	TEST_FLAGS = -lcheck
	OPEN = open
	VALGRIND_CMD = leaks --atExit -- 
endif

all: clean $(BIN_DIR)/tetris

install:
	$(MKDIR_P) $(BIN_DIR)
	$(CC) $(SOURCES) -o $(BIN_DIR)/tetris $(LDFLAGS) $(CFLAGS)

uninstall:
	rm -rf $(BIN_DIR) $(OBJECTS)

$(BIN_DIR)/tetris: $(SOURCES)
	$(MKDIR_P) $(@D)
	$(CC) $(SOURCES) -o $@ $(LDFLAGS) $(CFLAGS)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) *.gcno *.gcda *.info gcov_report tetris.tar.gz coverage_html highscore_tetris.txt

dvi:
	# cd dvi && doxygen
	$(OPEN) dvi/html/index.html

dist: clean
	tar -czvf tetris.tar.gz . makefile

test: clean
	$(MKDIR_P) $(BIN_DIR)
	$(CC) $(TETRIS_DIR)/tetris.c $(TETRIS_DIR)/templates.c $(TETRIS_DIR)/create.c $(TETRIS_DIR)/clean.c $(TESTS_DIR)/test.c -o $(BIN_DIR)/tetris.test $(LDFLAGS) $(CFLAGS) $(TEST_FLAGS)
	./$(BIN_DIR)/tetris.test

gcov_report: clean test
	lcov -d . -c -o coverage.info
	genhtml coverage.info --output-directory gcov_report
	$(OPEN) gcov_report/index.html

style_fix:
	clang-format -style=Google -i $(SOURCES) */*/*.c */*/*.h

style:
	clang-format -style=Google -n $(SOURCES) */*/*.c */*/*.h

leaks:
	$(VALGRIND_CMD) ./$(BIN_DIR)/tetris

valgrind_tetris: all
	$(VALGRIND_CMD) ./$(BIN_DIR)/tetris


run: $(BIN_DIR)/tetris
	./$(BIN_DIR)/tetris


