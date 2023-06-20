CC						= g++
CFLAGS					= -Wall -Werror -Wextra -std=c++17 -pedantic -g
LDFLAGS					= $(shell pkg-config --cflags --libs gtest)
GCOV_FLAGS				= -fprofile-arcs -ftest-coverage -fPIC
VALGRIND_FLAGS			= --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med

SRC_PROJECT_DIR			= logic/
SRC_TEST_DIR			= tests/
OBJ_PROJECT_DIR			= obj/logic/
OBJ_TEST_DIR			= obj/tests/

LIBRARY					= s21_matrix.a
BUILD_FOLDERS			:= $(shell mkdir -p $(OBJ_PROJECT_DIR); mkdir -p $(OBJ_TEST_DIR))
SRC_PROJECT				:= $(wildcard $(SRC_PROJECT_DIR)*.cpp)
SRC_TEST				:= $(wildcard $(SRC_TEST_DIR)*.cpp)
OBJ_PROJECT				:= $(patsubst $(SRC_PROJECT_DIR)%.cpp,$(OBJ_PROJECT_DIR)%.o,$(SRC_PROJECT))
OBJ_TEST				:= $(patsubst $(SRC_TEST_DIR)%.cpp,$(OBJ_TEST_DIR)%.o,$(SRC_TEST))

all: $(LIBRARY) test clean

$(LIBRARY): $(OBJ_PROJECT)
	ar rc $(LIBRARY) $(OBJ_PROJECT)
	ranlib $(LIBRARY)

test: $(LIBRARY) $(OBJ_TEST)
	$(CC) $(CFLAGS) $(OBJ_TEST) -o test $(LIBRARY) $(LDFLAGS)
	./test

gcov_report: $(OBJ_TEST)
	$(CC) $(CFLAGS) -o test $(OBJ_TEST) --coverage $(SRC_PROJECT) $(LDFLAGS)
	./test
	lcov -t "test" -o gcov.info -c -d .
	genhtml -o report gcov.info
	rm -rf ./*.gc*

$(OBJ_PROJECT_DIR)%.o: $(SRC_PROJECT_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_TEST_DIR)%.o: $(SRC_TEST_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm -rf $(OBJ_PROJECT_DIR)*	
	rm -rf $(OBJ_TEST_DIR)*
	rm -rf test
	rm -rf *.a
	rm -rf report
	rm -rf *.info
	rm -rf valgrind.txt

rebuild: clean test

open: 
	open report/index.html

valgrind: test
	valgrind $(VALGRIND_FLAGS) ./test
	! grep -n "ERROR SUMMARY" valgrind.txt | grep -v "0 errors"

clang:
	clang-format --style=google -i $(SRC_PROJECT_DIR)*
	clang-format --style=google -i $(SRC_TEST_DIR)*

.PHONY: all clean rebuild open clang valgrind docker
