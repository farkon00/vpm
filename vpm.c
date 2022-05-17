#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

// #include "./vpasm.h"

char *shift(int *argc, char ***argv)
{
  assert(*argc > 0);
  char *result = **argv;
  *argv += 1;
  *argc -= 1;
  return result;
}

void usage(char *program_name)
{
  fprintf(stderr, "[USAGE] %s <flags> [arguments]\n", program_name);
  fprintf(stderr, "-v <input_file>          Compile and run a vpasm file.\n");
  fprintf(stderr, "-h                       Display this help message.\n");
}

int main(int argc, char **argv)
{
  char* program_name = shift(&argc, &argv);

  if (argc == 0) {
    usage(program_name);
    fprintf(stderr, "[ERROR] No arguments were provided.\n");
    exit(1);
  }
  
  while (argc > 0) {
    const char* flag = shift(&argc, &argv);

    if (strcmp(flag, "-h") == 0) {
      usage(program_name);
      exit(1);
    } else if (strcmp(flag, "-v") == 0) {
      if (argc <= 0) {
	usage(program_name);
	fprintf(stderr, "[ERROR] No input file was provided.\n");
	exit(1);
      }
    } else {
      usage(program_name);
      fprintf(stderr, "[ERROR] Unknown flag %s\n", flag);
      exit(1);
    }
  }
  
  return 0;
}
