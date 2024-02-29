CC=gcc
CFLAGS=-Werror -Wall -Wextra

SRC=queue/queue.c

TEST_SRC=$(SRC) test/test.c test/test_queue.c
TEST_FLAGS=-lcheck -lm -lsubunit
TEST_EXEC=data_structs_test


tests: clean
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)

gcov_report: clean test
	$(CC) $(CFLAGS) --coverage $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS)
	./$(TEST_EXEC)
	lcov -t "$(TEST_EXEC)" -o $(TEST_EXEC)_gcov.info -c -d .
	genhtml -o report $(TEST_EXEC)_gcov.info
	open report/index.html

clean:
	rm -rf $(TEST_EXEC)
	rm -rf *.info *.gcda *.gcno
	rm -rf report/
