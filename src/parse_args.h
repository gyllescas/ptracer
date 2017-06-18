#ifndef __PARSE_ARGS_H__
#define __PARSE_ARGS_H__

#include <stdbool.h>

typedef struct _program_arguments_t {
  char **functions;
  int num_functions;
  char *output;
  char **child_args;
} program_arguments_t;

void usage(void);
bool parse_arguments(int argc, char *argv[], program_arguments_t *args);
void program_arguments_free(program_arguments_t *args);

#endif // __PARSE_ARGS_H__
