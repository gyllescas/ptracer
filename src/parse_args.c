#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_args.h"

#define FUNCTION_DELIMITER ","

void
usage(void)
{
  fprintf(stderr,
          "ptrace [ptrace args] program [program args]\n"
          "\n"
          "ptrace arguments:\n"
          "--functions=, -f\t\tFunction to trace\n"
          "--output=, -o\t\t\tOutput File\n");
}

static int
count_split(char *str, char *delimiter)
{
  int count = 1;
  char *ptr = str;
  while((ptr = strpbrk(ptr, delimiter)) != NULL) {
    count++;
    ptr++;
  }

  return count;
}

bool
parse_arguments(int argc, char *argv[], program_arguments_t *args)
{
  int c;
  char *tmp_str;
  int i;
  static struct option long_options[] = {
    {"functions", required_argument, NULL, 'f'},
    {"output", required_argument, NULL, 'o'},
    { 0, 0, 0, 0 }
  };

  optind = 0;

  memset(args, 0, sizeof(*args));

  while((c = getopt_long(argc, argv, "f:o:", long_options, NULL)) != -1) {

    switch(c) {
    case 'f':

      tmp_str = strdup(optarg);

      if(tmp_str == NULL) {
        return false;
      }

      args->num_functions = count_split(tmp_str, FUNCTION_DELIMITER);
      args->functions = malloc(args->num_functions * sizeof(char *));
      if(args->functions == NULL) {
        free(tmp_str);
        return false;
      }

      for(i = 0; i < args->num_functions; i++) {
        args->functions[i] =
          strdup(strtok(i == 0 ? tmp_str : NULL, FUNCTION_DELIMITER));
        if(args->functions[i] == NULL) {
          free(tmp_str);
          return false;
        }
      }

      free(tmp_str);
      break;

    case 'o':

      args->output = strdup(optarg);

      if(args->output == NULL) {
        return false;
      }
      break;

    default:
      usage();
      return false;
    }
  }

  if(optind == argc) {
    usage();
    return false;
  }

  args->child_args = calloc(((argc - optind) + 1), sizeof(char *));
  if(args->child_args == NULL) {
    return false;
  }

  for(i = 0; optind < argc; optind++, i++) {
    args->child_args[i] = strdup(argv[optind]);
  }

  if(args->num_functions == 0) {
    return false;
  }

  return true;
}

void
program_arguments_free(program_arguments_t *args)
{
  int i;

  for(i = 0; i < args->num_functions; i++) {
    free(args->functions[i]);
  }

  free(args->functions);
  free(args->output);
}
