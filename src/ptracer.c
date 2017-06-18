#include <stdlib.h>
#include <stdio.h>

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
    fprintf(stderr, "Failed to parse arguments\n");
    return EXIT_FAILURE;
  }

  if(!trace_find_functions(&args, &trace_info)) {
    fprintf(stderr, "Failed to find functions\n");
    return EXIT_FAILURE;
  }

  if(!trace_launch(&args, &trace_info)) {
    fprintf(stderr, "Failed to launch child\n");
    return EXIT_FAILURE;
  }

  if(!trace_add_breakpoints(&trace_info)) {
    fprintf(stderr, "Failed to add breakpoints\n");
    return EXIT_FAILURE;
  }

  if(!results_initialize(&results, &trace_info)) {
    fprintf(stderr, "Failed to initialize results data\n");
    return EXIT_FAILURE;
  }

  if(!trace_function_calls(&trace_info, &results)) {
    fprintf(stderr, "Failed to trace function calls\n");
    return EXIT_FAILURE;
  }

  if(!results_output(&args, &results)) {
    fprintf(stderr, "Failed to output results\n");
    return EXIT_FAILURE;
  }

  program_arguments_free(&args);

  return EXIT_SUCCESS;
}
