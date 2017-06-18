#ifndef __RESULTS_H__
#define __RESULTS_H__

#include <stdbool.h>

#include "parse_args.h"
#include "trace_info.h"

typedef struct _function_invocation_t function_invocation_t;

struct _function_invocation_t {
  int index;
  int instruction_count;

  function_invocation_t *next;
};

typedef struct _results_t {
  char **function_names;
  int num_functions;
  function_invocation_t *invocations;
} results_t;

bool results_initialize(results_t *results, trace_info_t *trace_info);
bool results_output(program_arguments_t *args, results_t *results);

#endif // __RESULTS_H__
