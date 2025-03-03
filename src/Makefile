CC = gcc
FLAGS = -Wall -Wextra -std=c11 -g
LINUX_FLAGS = -lsubunit -lrt -lpthread -lm
TEST_TARGET = ./test

OS := $(shell uname -s)

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif

ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all : clean

test :
	make -C ./io test
	make -C ./maze test



style_check :
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Adecvatnost     ┃"
	@echo "┗=========================================┛"
	@cp ./linters/.clang-format .
	@find . -name "*.c" -o -name "*.h" | xargs clang-format -n
	@rm ./.clang-format

format_style :
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Adecvatnost   ┃"
	@echo "┗=========================================┛"
	@cp ./linters/.clang-format .
	@find . -name "*.c" -o -name "*.h" | xargs clang-format -i
	@rm .clang-format

style_check_cheloveka_cotorogo_po_golove_bum_bum_bum :
	@echo "┏=========================================┓"
	@echo "┃  Checking your code for Google Style    ┃"
	@echo "┗=========================================┛"
	@find . -name "*.c" -o -name "*.h" | xargs clang-format -n -style="{BasedOnStyle: Google}"

format_style_cheloveka_cotorogo_po_golove_bum_bum_bum  :
	@echo "┏=========================================┓"
	@echo "┃  Formatting your code for Google Style  ┃"
	@echo "┗=========================================┛"
	@find . -name "*.c" -o -name "*.h" | xargs clang-format -i -style="{BasedOnStyle: Google}"


clean :
	@echo "Deleting unnecessary files..."
	rm -rf *.o *.a *.dSYM **/*.dSYM *.log **/*.log *.gc*
	make -C ./io clean
	make -C ./maze clean

full_clean : clean
	rm -rf *.html

.PHONY: all clean test  style_check
