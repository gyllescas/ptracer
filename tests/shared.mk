.PHONY: all clean run

CFLAGS := -Wall -Wextra -Werror -g -fprofile-arcs -ftest-coverage -I ../../ -ldwarf
LDLIBS := -lcmocka

PROGS += $(TEST)

all: $(PROGS)

$(TEST): test_% : test_%.c ../tests.h ../../src/%.c Makefile
	$(CC) $(TEST).c $(CFLAGS) $(LDLIBS) -o $@

run: $(TEST)
	./$(TEST)

coverage: run
	gcov -l *.gcda

clean:
	rm -rf $(PROGS) *.o *~ *.gcda *.gcno *.gcov
