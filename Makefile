CC=gcc
CFLAGS=-Werror -Wall -Wextra

HEADERS=queue/queue.h
SRC=queue/queue.c


TEST_HEADERS=test/test.h
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
