#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "./vpasm.h"


Instruction BUILD_INST(Instruction_Type type, size_t arg_count)
{
  return (Instruction) {
    .type = type,
    .arg_count = arg_count
  };
}

Instruction INST_MOV(char* reg, char* value) {
  Instruction inst = BUILD_INST(INSTRUCTION_MOV, 2);
  strncpy(inst.arguments[0], reg, 4);
  strncpy(inst.arguments[1], value, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_SUM(char* regOne, char* regTwo) {
  Instruction inst = BUILD_INST(INSTRUCTION_SUM, 2);
  strncpy(inst.arguments[0], regOne, 4);
  strncpy(inst.arguments[1], regTwo, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_SUB(char* regOne, char* regTwo) {
  Instruction inst = BUILD_INST(INSTRUCTION_SUB, 2);
  strncpy(inst.arguments[0], regOne, 4);
  strncpy(inst.arguments[1], regTwo, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_MULT(char* regOne, char* regTwo) {
  Instruction inst = BUILD_INST(INSTRUCTION_MULT, 2);
  strncpy(inst.arguments[0], regOne, 4);
  strncpy(inst.arguments[1], regTwo, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_DIV(char* regOne, char* regTwo) {
  Instruction inst = BUILD_INST(INSTRUCTION_DIV, 2);
  strncpy(inst.arguments[0], regOne, 4);
  strncpy(inst.arguments[1], regTwo, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_JMP(char* jmpLoc) {
  Instruction inst = BUILD_INST(INSTRUCTION_JMP, 1);
  strncpy(inst.arguments[0], jmpLoc, 4);
  assert(inst.arguments[0][3] == '\0');
  return inst;
}
Instruction INST_JMP_IF_ZERO(char* jmpLoc) {
  Instruction inst = BUILD_INST(INSTRUCTION_JMP_IF_ZERO, 1);
  strncpy(inst.arguments[0], jmpLoc, 4);
  assert(inst.arguments[0][3] == '\0');
  return inst;
}
Instruction INST_DEBUG_PRINT(char* reg) {
  Instruction inst = BUILD_INST(INSTRUCTION_DEBUG_PRINT, 1);
  strncpy(inst.arguments[0], reg, 4);
  assert(inst.arguments[0][3] == '\0');
  return inst;
}
Instruction INST_HALT() {
  return (Instruction) {.type = INSTRUCTION_HALT};
}

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
  fprintf(stderr, "-v <input.vpasm> [-o output.vpm]   Compile vpasm file to a .vpm binary file.\n");
  fprintf(stderr, "-e <program.vpm>                   Execute a .vpm file\n");
  fprintf(stderr, "-h                                 Display this help message.\n");
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

void program_from_bin_file(Program* program, char* file_path)
{
  FILE *f = fopen(file_path, "rb");
  if (f == NULL) {
    fprintf(stderr, "[ERROR] Could not open file `%s`\n", file_path);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  assert(fsize % sizeof(program->instructions[0]) == 0);
  fseek(f, 0, SEEK_SET);

  program->instructions = malloc(PROGRAM_CAPACITY * sizeof(Instruction));

  program->program_size = fread(program->instructions, sizeof(Instruction), fsize / sizeof(Instruction), f);

  fclose(f);
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

    if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0) {
      usage(program_name);
      exit(0);
    } else if (strcmp(flag, "-v") == 0) {
      if (argc < 1) {
        usage(program_name);
        exit(1);
      }

      char* input_file = shift(&argc, &argv);
      char* output_file = "output.vpm";
      if (argc == 0) {
        // No output path provided
        String_View extension = cstr_to_sv(input_file);
        String_View input_name = sv_chop_by_delimiter(&extension, '.');

        output_file = strcat(sv_to_cstr(input_name), ".vpm");
      }

      Program program = {0};

      assert(0 && "TODO: Implement load from .vpasm file");
      // vpasm_load_from_file(&program, input_file);

      program_as_bin_file(&program, output_file);
    } else if (strcmp(flag, "-e") == 0) {
      if (argc < 1) {
        usage(program_name);
        exit(1);
      }

      char* input_file = shift(&argc, &argv);
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
    } else {
      usage(program_name);
      fprintf(stderr, "[ERROR] Unknown flag %s\n", flag);
      exit(1);
    }
  }

  return 0;
}
