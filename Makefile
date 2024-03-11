NAME=xlibc


CC=gcc
CFLAGS=-Werror -Wall -Wextra -O3 -march=native


HEADERS=lib/string_array.h lib/queue.h lib/types.h lib/stack.h lib/list.h  \
	lib/forward_list.h lib/array.h lib/hash.h lib/hashmap.h lib/hashset.h \
	lib/linear_allocator.h lib/pool_allocator.h

SRC=lib/string_array.c lib/types.c lib/queue.c lib/stack.c lib/list.c \
	lib/forward_list.c lib/array.c lib/hash.c lib/hashmap.c lib/hashset.c \
	lib/linear_allocator.c lib/pool_allocator.c
	
OBJ=$(SRC:.c=.o)


TEST_HEADERS=test/test.h
TEST_SRC=$(SRC) test/test.c test/test_queue.c test/test_stack.c test/test_list.c \
	test/test_forward_list.c test/test_array.c test/test_hashmap.c test/test_hashset.c \
	test/test_linear_allocator.c test/test_pool_allocator.c 

TEST_FLAGS=-lcheck -lm -lsubunit
TEST_EXEC=$(NAME)_test



all: clean shared_lib static_lib


static_lib: clean $(OBJ)
	ar rcs $(NAME).a $(OBJ)
	

shared_lib: clean $(OBJ)
	$(CC) -shared -fpic -flto -o $(NAME).so $(OBJ)


%.o: %.c
	$(CC) $(CFLAGS) -flto -c $< -o $@


tests: clean
	$(CC) $(CFLAGS) -g -fsanitize=address -fsanitize=undefined $(TEST_SRC) -o $(TEST_EXEC) $(TEST_FLAGS) 
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

install:


uninstall:


dvi:
	open README.md

dist:


clean:
	rm -rf $(TEST_EXEC) a.out
	rm -rf *.info *.gcda *.gcno
	rm -rf report/
	rm -rf docs/*
	rm -rf lib/*.o $(NAME).so $(NAME).a
