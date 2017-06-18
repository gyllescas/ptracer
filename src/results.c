#include <stdlib.h>
#include <string.h>

#include "results.h"

bool
results_initialize(results_t *results, trace_info_t *trace_info)
{
  int i;

  results->num_functions = trace_info->num_func_infos;
  results->function_names = malloc(results->num_functions * sizeof(char *));

  if(results->function_names == NULL) {
    return false;
  }

  for(i = 0; i < results->num_functions; i++) {
    results->function_names[i] = strdup(trace_info->function_infos[i].name);
    if(results->function_names[i] == NULL) {
      while(i--) {
        free(results->function_names[i]);
      }
      return false;
    }
  }

  return true;
}

bool
results_output(program_arguments_t *args, results_t *results)
{
  (void)args;
  (void)results;
  return true;
}
