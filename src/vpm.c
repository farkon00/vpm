#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "./vpasm.h"

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
  fprintf(stderr, "-r <input.vpasm> [-o output.vpm]   Compile vpasm file to a .vpm binary file and execute output file.\n");
  fprintf(stderr, "-v <input.vpasm> [-o output.vpm]   Compile vpasm file to a .vpm binary file.\n");
  fprintf(stderr, "-e <program.vpm>                   Execute a .vpm file\n");
  fprintf(stderr, "-h --help                          Display this help message.\n");
}

void program_as_bin_file(Program* program, char* output_file)
{
  FILE *f = fopen(output_file, "wb");
  if (f == NULL) {
    fprintf(stderr, "[ERROR] Could not open file `%s`\n", output_file);
    exit(1);
  }

  fwrite(program->instructions, sizeof(Instruction), program->program_size, f);

  fclose(f);
}

char* get_output_file(char* input_file)
{
  String_View extension = cstr_to_sv(input_file);
  String_View input_name = sv_chop_by_delimiter(&extension, '.');

  return strcat(sv_to_cstr(input_name), ".vpm");
}

void program_from_bin_file(Program* program, char* file_path)
{
  FILE *f = fopen(file_path, "rb");
  if (f == NULL) {
    fprintf(stderr, "[ERROR] Could not open file `%s`\n", file_path);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  if (fsize % sizeof(program->instructions[0]) != 0) {
    fprintf(stderr, "[ERROR] File size is not correct for a vpm file.\n");
    fprintf(stderr, "[NOTE] %s is most likely not a valid vpm file.\n", file_path);
    exit(1);
  }

  fseek(f, 0, SEEK_SET);

  program->instructions = malloc(PROGRAM_CAPACITY * sizeof(Instruction));

  program->program_size = fread(program->instructions, sizeof(Instruction), fsize / sizeof(Instruction), f);

  fclose(f);
}

int compile_vpasm_to_bin(int argc, char **argv, char *program_name, bool allow_flags)
{
  if (argc < 1) {
    usage(program_name);
    exit(1);
  }

  char* input_file = shift(&argc, &argv);
  int shifted = 1;
  char* output_file = "output.vpm";
  if (argc == 0 || !allow_flags) {
    // No output path provided or flags are not allowed
    output_file = get_output_file(input_file); 
  } else {
    char *flag = shift(&argc, &argv);
    shifted++;
    if (strcmp(flag, "-o") != 0) {
      usage(program_name);
      fprintf(stderr, "Unknown flag: %s\n", flag);
      exit(1);
    }
    if (argc == 0) {
      usage(program_name);
      fprintf(stderr, "[ERROR] No output file name provided for flag -o\n");
      exit(1);
    }
    output_file = shift(&argc, &argv);
    shifted++;
  }

  Program program = {0};

  vpasm_load_from_file(&program, input_file);

  program_as_bin_file(&program, output_file);

  return shifted;
}

void execute_bin_file(int argc, char **argv, char *program_name, bool use_prog_name)
{
  if (argc < 1 && !use_prog_name) {
    usage(program_name);
    exit(1);
  }

  char* input_file;
  if (use_prog_name) {
    input_file = program_name;
  } else {
    input_file = shift(&argc, &argv);
  }
  printf("%s\n", input_file);
  Memory memory = {0};
  Program program = {0};

  vpasm_initialize_registers(&memory);

  program_from_bin_file(&program, input_file);

  vpasm_load_program(&memory, &program);
  vpasm_exec_program(&memory, 100, false);

  vpasm_debug_print_registers(stdout, &memory);
  vpasm_free(&memory);
  exit(0);
}

int main(int argc, char **argv)
{
  char* program_name = shift(&argc, &argv);
  char* output_file = NULL;

  if (argc == 0) {
    usage(program_name);
    fprintf(stderr, "[ERROR] No arguments were provided.\n");
    exit(1);
  }

  while (argc > 0) {
    const char* flag = shift(&argc, &argv);

    if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0) {
      usage(program_name);
      exit(0);
    } else if (strcmp(flag, "-r") == 0) {
      compile_vpasm_to_bin(argc, argv, program_name, false);
      output_file = get_output_file(shift(&argc, &argv));
      execute_bin_file(argc, argv, output_file, true);
    } else if (strcmp(flag, "-v") == 0) {
      int shifted = compile_vpasm_to_bin(argc, argv, program_name, true);
      for (int i = 0; i < shifted; i++) {
        shift(&argc, &argv);
      }
    } else if (strcmp(flag, "-e") == 0) {
      execute_bin_file(argc, argv, program_name, false);
    } else {
      usage(program_name);
      fprintf(stderr, "[ERROR] Unknown flag %s\n", flag);
      exit(1);
    }
  }

  return 0;
}
