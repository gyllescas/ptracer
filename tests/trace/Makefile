TEST := test_trace

TEST_PROGS := test_prog_no_debug
TEST_PROGS += test_prog_with_debug

PROGS += $(TEST_PROGS)

include ../shared.mk


# Test progs are not rebuilt unless necessary because function locations are
# hardcoded into tests
test_progs: test_prog_no_debug test_prog_with_debug

TEST_PROG_SRC = test_prog.c
test_prog_no_debug: $(TEST_PROG_SRC)
	$(CC) $(TEST_PROG_SRC) -o $@

test_prog_with_debug: $(TEST_PROG_SRC)
	$(CC) $(TEST_PROG_SRC) -g -o $@
