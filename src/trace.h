#ifndef __TRACE_H__
#define __TRACE_H__

#include <stdbool.h>

#include "parse_args.h"
#include "results.h"
#include "trace_info.h"

bool trace_find_functions(program_arguments_t *args, trace_info_t *trace_info);
bool trace_add_breakpoints(trace_info_t *trace_info);
bool trace_launch(program_arguments_t *args, trace_info_t *trace_info);
bool trace_function_calls(trace_info_t *trace_info, results_t *results);

#endif // __TRACE_H__
