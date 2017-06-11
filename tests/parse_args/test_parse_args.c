#include <stdbool.h>

#include "../tests.h"
#include "src/parse_args.c"

static void
test_usage(UNUSED void **state)
{
  usage();
}

static void
test_parse_arguments_invalid_args(UNUSED void **state)
{
  char *argv[] = {"ptracer", "-f", "junk", "foo"};
  program_arguments_t program_args;

  assert_false(parse_arguments(2, argv, &program_args));
  program_arguments_free(&program_args);

  argv[1] = "-aasdf";
  assert_false(parse_arguments(4, argv, &program_args));
  program_arguments_free(&program_args);

  argv[1] = "-o";
  assert_false(parse_arguments(2, argv, &program_args));
  program_arguments_free(&program_args);
}

static void
test_parse_arguments_parse_single_function(UNUSED void **state)
{
  {
    int argc = 4;
    char *argv[] = {"ptracer", "-f", "foo", "prog"};
    program_arguments_t program_args;

    assert_true(parse_arguments(argc, argv, &program_args));
    assert_int_equal(program_args.num_functions, 1);
    assert_non_null(program_args.functions);
    assert_string_equal(program_args.functions[0], "foo");
    program_arguments_free(&program_args);
  }

  {
    int argc = 3;
    char *argv[] = {"ptracer", "-ffoo", "prog"};
    program_arguments_t program_args;

    assert_true(parse_arguments(argc, argv, &program_args));
    assert_int_equal(program_args.num_functions, 1);
    assert_non_null(program_args.functions);
    assert_string_equal(program_args.functions[0], "foo");
    program_arguments_free(&program_args);
  }

  {
    int argc = 3;
    char *argv[] = {"ptracer", "--function=foo", "prog"};
    program_arguments_t program_args;

    assert_true(parse_arguments(argc, argv, &program_args));
    assert_int_equal(program_args.num_functions, 1);
    assert_non_null(program_args.functions);
    assert_string_equal(program_args.functions[0], "foo");
    program_arguments_free(&program_args);
  }
}

static void
test_parse_arguments_parse_multiple_functions(UNUSED void **state)
{
  {
    int argc = 3;
    char *argv[] = {"ptracer", "-ffoo,bar", "prog"};
    program_arguments_t program_args;

    assert_true(parse_arguments(argc, argv, &program_args));
    assert_int_equal(program_args.num_functions, 2);
    assert_non_null(program_args.functions);
    assert_string_equal(program_args.functions[0], "foo");
    assert_string_equal(program_args.functions[1], "bar");
    program_arguments_free(&program_args);
  }

  {
    int argc = 3;
    char *argv[] = {"ptracer", "-ffoo,bar,baz", "prog"};
    program_arguments_t program_args;

    assert_true(parse_arguments(argc, argv, &program_args));
    assert_int_equal(program_args.num_functions, 3);
    assert_non_null(program_args.functions);
    assert_string_equal(program_args.functions[0], "foo");
    assert_string_equal(program_args.functions[1], "bar");
    assert_string_equal(program_args.functions[2], "baz");
    program_arguments_free(&program_args);
  }

  {
    int argc = 4;
    char *argv[] = {"ptracer", "-f", "foo,bar,baz", "prog"};
    program_arguments_t program_args;

    assert_true(parse_arguments(argc, argv, &program_args));
    assert_int_equal(program_args.num_functions, 3);
    assert_non_null(program_args.functions);
    assert_string_equal(program_args.functions[0], "foo");
    assert_string_equal(program_args.functions[1], "bar");
    assert_string_equal(program_args.functions[2], "baz");
    program_arguments_free(&program_args);
  }
}

static void
test_parse_arguments_parse_output_file(UNUSED void **state)
{
  {
    int argc = 3;
    char *argv[] = {"ptracer", "-ooutput.txt", "prog"};
    program_arguments_t program_args;


    assert_false(parse_arguments(argc, argv, &program_args));
    assert_string_equal(program_args.output, "output.txt");
    program_arguments_free(&program_args);
  }

  {
    int argc = 3;
    char *argv[] = {"ptracer", "--output=output.txt", "prog"};
    program_arguments_t program_args;


    assert_false(parse_arguments(argc, argv, &program_args));
    assert_string_equal(program_args.output, "output.txt");
    program_arguments_free(&program_args);
  }
}

int
main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_usage),
    cmocka_unit_test(test_parse_arguments_invalid_args),
    cmocka_unit_test(test_parse_arguments_parse_single_function),
    cmocka_unit_test(test_parse_arguments_parse_multiple_functions),
    cmocka_unit_test(test_parse_arguments_parse_output_file),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
