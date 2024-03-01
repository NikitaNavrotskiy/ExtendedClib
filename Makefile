NAME=ds_lib

CC=gcc
CFLAGS=-Werror -Wall -Wextra -O3

HEADERS=lib/queue.h lib/types.h
SRC=lib/queue.c
OBJ=$(SRC:.c=.o)

TEST_HEADERS=test/test.h
TEST_SRC=$(SRC) test/test.c test/test_queue.c
TEST_FLAGS=-lcheck -lm -lsubunit
TEST_EXEC=data_structs_test


static_lib: $(OBJ)
	ar rcs $(NAME).a $< 
	

shared_lib: $(OBJ)
	$(CC) -shared -o $(NAME).so $(OBJ)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


tests: clean
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)

gcov_report: clean test
	$(CC) $(CFLAGS) --coverage $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)
	lcov -t "$(TEST_EXEC)" -o $(TEST_EXEC)_gcov.info -c -d .
	genhtml -o report $(TEST_EXEC)_gcov.info
	open report/index.html

doc:
	doxygen
	open docs/html/index.html

clang-format:
	clang-format -i $(SRC) $(TEST_SRC) $(HEADERS) $(TEST_HEADERS)

clean:
	rm -rf $(TEST_EXEC)
	rm -rf *.info *.gcda *.gcno
	rm -rf report/
	rm -rf docs/*
	rm -rf lib/*.o $(NAME).so $(NAME).a
