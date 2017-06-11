#include <stdlib.h>

#include "parse_args.h"
#include "results.h"
#include "trace.h"

int
main(int argc, char *argv[])
{
  program_arguments_t args;
  trace_info_t trace_info;
  results_t results;

  if(!parse_arguments(argc, argv, &args)) {
    return EXIT_FAILURE;
  }

  if(!trace_find_functions(&args, &trace_info)) {
    return EXIT_FAILURE;
  }

  if(!trace_run(&args, &trace_info)) {
    return EXIT_FAILURE;
  }

  if(!results_output(&args, &results)) {
    return EXIT_FAILURE;
  }

  program_arguments_free(&args);

  return EXIT_SUCCESS;
}
