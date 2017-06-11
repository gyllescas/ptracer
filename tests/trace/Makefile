TEST := test_trace

TEST_PROGS := test_prog_no_debug
TEST_PROGS += test_prog_with_debug

include ../shared.mk

# Test progs are not rebuilt unless necessary because function locations are
# hardcoded into tests
test_progs: test_prog_no_debug test_prog_with_debug

test_prog_no_debug: test_prog.c
	$(CC) test_prog.c -o $@

test_prog_with_debug: test_prog.c
	$(CC) test_prog.c -g -o $@
