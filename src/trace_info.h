#ifndef __TRACE_INFO_H__
#define __TRACE_INFO_H__

#include <stdint.h>
#include <sys/types.h>
#include <libdwarf/libdwarf.h>
#include <libdwarf/dwarf.h>

typedef struct _function_information_t {
  char *name;
  uintptr_t ip;
  long original;
} function_information_t;

typedef struct _trace_info_t {
  Dwarf_Debug dbg;
  int prog_fd;
  function_information_t *function_infos;
  int num_func_infos;
  int next_func;
  pid_t child_pid;
} trace_info_t;

#endif // __TRACE_INFO_H__
