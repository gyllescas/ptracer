.PHONY: all clean run

CFLAGS := -Wall -Wextra -Werror -g -fprofile-arcs -ftest-coverage -I ../../
LDLIBS := -lcmocka -ldwarf -lelf

PROGS += $(TEST)

all: $(PROGS)

$(PROGS): Makefile

$(TEST): test_% : test_%.c ../tests.h ../../src/%.c Makefile
	$(CC) $(TEST).c $(CFLAGS) $(LDLIBS) -o $@

run: $(TEST) $(PROGS)
	./$(TEST)

coverage: run
	gcov -l *.gcda

clean:
	rm -rf $(PROGS) *.o *~ *.gcda *.gcno *.gcov
