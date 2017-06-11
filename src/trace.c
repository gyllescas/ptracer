#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "trace.h"

static bool
trace_info_initialize(program_arguments_t *args, trace_info_t *trace_info)
{
  trace_info->prog_fd = -1;
  trace_info->function_infos = calloc(args->num_functions,
                                      sizeof(*trace_info->function_infos));
  trace_info->num_func_infos = args->num_functions;
  trace_info->next_func = 0;

  return trace_info->function_infos != NULL;
}

static void
trace_info_free(trace_info_t *trace_info)
{
  free(trace_info->function_infos);
  if(trace_info->prog_fd != -1) {
    close(trace_info->prog_fd);
  }

  trace_info->function_infos = NULL;
  trace_info->prog_fd = -1;
}

static bool
trace_is_target_function(program_arguments_t *args,
                         trace_info_t *trace_info,
                         Dwarf_Die die)
{
  Dwarf_Error err;
  Dwarf_Half tag;
  Dwarf_Attribute attr;
  Dwarf_Addr addr;
  char *name;
  int i;
  int res;

  (void) trace_info;

  if(dwarf_tag(die, &tag, &err) != DW_DLV_OK) {
    fprintf(stderr, "dwarf_tag failed\n");
    return -1;
  }

  if(tag != DW_TAG_subprogram) {
    return 0;
  }

  res = dwarf_attr(die, DW_AT_name, &attr, &err);

  if(res == DW_DLV_ERROR) {
    fprintf(stderr, "dwarf_attr failed\n");
    return -1;
  }

  res = dwarf_formstring(attr, &name, &err);

  if(res == DW_DLV_ERROR) {
    fprintf(stderr, "dwarf_formstring failed\n");
    return -1;
  }

  for(i = 0; i < args->num_functions; i++) {
    if(strcmp(args->functions[i], name) == 0) {
      trace_info->function_infos[trace_info->next_func].name = strdup(name);
      if(trace_info->function_infos[trace_info->next_func].name == NULL) {
        return -1;
      }
      if(dwarf_lowpc(die, &addr, &err) == DW_DLV_ERROR) {
        fprintf(stderr, "Failed to get low pc\n");
        free(trace_info->function_infos[trace_info->next_func].name);
        trace_info->function_infos[trace_info->next_func].name = NULL;
        return -1;
      }
      trace_info->function_infos[trace_info->next_func].ip = addr;
      return 1;
    }
  }

  return 0;
}

static int
trace_cu_find_functions(program_arguments_t *args,
                        trace_info_t *trace_info,
                        Dwarf_Die cu_die)
{
  int count = 0;
  Dwarf_Error err;
  Dwarf_Die child_die;
  int res;

  res = dwarf_child(cu_die, &child_die, &err);

  if(res == DW_DLV_ERROR) {
    fprintf(stderr, "dwarf_child failed in %s\n", __FUNCTION__);
    return -1;
  }

  while(1) {

    res = trace_is_target_function(args, trace_info, child_die);

    if(res < 0) {
      return -1;
    }
    else if(res == 1) {
      count++;
    }

    res = dwarf_siblingof(trace_info->dbg, child_die, &child_die, &err);

    if(res == DW_DLV_ERROR) {
      fprintf(stderr, "dwarf_siblingof failed in %s\n", __FUNCTION__);
      return -1;
    }
    else if(res == DW_DLV_NO_ENTRY) {
      break;
    }
  }

  return count;
}

bool
trace_find_functions(program_arguments_t *args, trace_info_t *trace_info)
{
  int res;
  Dwarf_Die previous_die = 0;
  Dwarf_Die cu_die;
  Dwarf_Error err;
  Dwarf_Unsigned cu_header_length;
  Dwarf_Unsigned abbrev_offset;
  Dwarf_Unsigned next_cu_header;
  Dwarf_Half version_stamp;
  Dwarf_Half address_size;
  int found_functions;
  int total_found_functions = 0;

  trace_info_initialize(args, trace_info);

  trace_info->prog_fd = open(args->child_args[0], O_RDONLY);

  if(trace_info->prog_fd < 0) {
    fprintf(stderr, "Failed to open %s\n", args->child_args[0]);
    goto failure;
  }

  if(dwarf_init(trace_info->prog_fd, DW_DLC_READ, 0, 0,
                &trace_info->dbg, &err) != DW_DLV_OK) {
    fprintf(stderr, "Failed DWARF initialization\n");
    goto failure;
  }

  while(((res = dwarf_next_cu_header(trace_info->dbg, &cu_header_length,
                                     &version_stamp, &abbrev_offset,
                                     &address_size, &next_cu_header, &err))
         != DW_DLV_NO_ENTRY) &&
        (total_found_functions < trace_info->num_func_infos)) {

    if(res == DW_DLV_ERROR) {
      fprintf(stderr, "dwarf_next_cu_header failed\n");
      goto failure;
    }

    while((res = dwarf_siblingof(trace_info->dbg, previous_die,
                                 &cu_die, &err)) != DW_DLV_NO_ENTRY) {

      if(res == DW_DLV_ERROR) {
        fprintf(stderr, "Failed to find sibling of CU die\n");
        goto failure;
      }

      found_functions = trace_cu_find_functions(args, trace_info, cu_die);
      if(found_functions < 0) {
        goto failure;
      }
      total_found_functions += found_functions;
      previous_die = cu_die;
    }
  }

  if(trace_info->num_func_infos != total_found_functions) {
    goto failure;
  }

  return true;

 failure:
  trace_info_free(trace_info);
  return false;
}

bool
trace_add_breakpoints(pid_t child_pid, trace_info_t *trace_info)
{
  (void)child_pid;
  (void)trace_info;

  return false;
}

bool
trace_run(program_arguments_t *args, trace_info_t *trace_info)
{
  (void)args;
  (void)trace_info;

  return false;
}
