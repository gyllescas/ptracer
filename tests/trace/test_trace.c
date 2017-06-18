#include <stdbool.h>

#include "../tests.h"
#include "src/trace.c"

static void
test_trace_find_functions_nonexistant_file(UNUSED void **state)
{
  program_arguments_t args;
  trace_info_t trace_info;
  char *child_args[] = {"does_not_exit", NULL};

  args.child_args = child_args;
  assert_false(trace_find_functions(&args, &trace_info));
}

static void
test_trace_find_functions_no_debug_information(UNUSED void **state)
{
  program_arguments_t args;
  trace_info_t trace_info;
  char *child_args[] = {"test_prog_no_debug", NULL};
  char *functions[] = {"func1"};

  args.child_args = child_args;
  args.functions = functions;
  args.num_functions = 1;
  assert_false(trace_find_functions(&args, &trace_info));
}

static void
test_trace_find_functions_nonexistant_function(UNUSED void **state)
{
  program_arguments_t args;
  trace_info_t trace_info;
  char *child_args[] = {"test_prog", NULL};
  char *functions[] = {"doesnt_exist"};

  args.child_args = child_args;
  args.functions = functions;
  args.num_functions = 1;
  assert_false(trace_find_functions(&args, &trace_info));
}

static void
test_trace_find_functions_single_function(UNUSED void **state)
{
  program_arguments_t args;
  trace_info_t trace_info;
  char *child_args[] = {"test_prog_with_debug", NULL};
  char *functions[] = {"func1"};

  args.child_args = child_args;
  args.functions = functions;
  args.num_functions = 1;
  assert_true(trace_find_functions(&args, &trace_info));
  assert_string_equal(trace_info.function_infos[0].name, functions[0]);
  //assert_int_equal(0x4004f6, trace_info.function_infos[0].ip);
}

static void
test_trace_launch_invalid_child(UNUSED void **state)
{
  program_arguments_t args;
  trace_info_t trace_info;
  char *child_args[] = {"does_not_exit", NULL};

  args.child_args = child_args;
  assert_false(trace_launch(&args, &trace_info));
}

void
test_trace_launch_child(UNUSED void **state)
{
  program_arguments_t args;
  trace_info_t trace_info;
  char *child_args[] = {"./test_prog_with_debug", NULL};

  args.child_args = child_args;
  assert_true(trace_launch(&args, &trace_info));

  kill(trace_info.child_pid, SIGKILL);
}

int
main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_trace_find_functions_nonexistant_file),
    cmocka_unit_test(test_trace_find_functions_no_debug_information),
    cmocka_unit_test(test_trace_find_functions_nonexistant_function),
    cmocka_unit_test(test_trace_find_functions_single_function),
    cmocka_unit_test(test_trace_launch_invalid_child),
    cmocka_unit_test(test_trace_launch_child),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
