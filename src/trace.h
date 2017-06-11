#ifndef __TRACE_H__
#define __TRACE_H__

#include <stdbool.h>
#include <sys/types.h>
#include <stdint.h>
#include <libdwarf/libdwarf.h>
#include <libdwarf/dwarf.h>

#include "parse_args.h"

typedef struct {
  char *name;
  intptr_t ip;
} function_information_t;

typedef struct {
  Dwarf_Debug dbg;
  int prog_fd;
  function_information_t *function_infos;
  int num_func_infos;
  int next_func;
} trace_info_t;

bool trace_find_functions(program_arguments_t *args, trace_info_t *trace_info);
bool trace_add_breakpoints(pid_t child_pid, trace_info_t *trace_info);
bool trace_run(program_arguments_t *args, trace_info_t *trace_info);

#endif // __TRACE_H__
