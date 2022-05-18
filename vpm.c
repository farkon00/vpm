#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

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
      Memory memory = {0};
      Program program = {0};

      vpasm_add_instruction(&program, (Instruction) {.type=INSTRUCTION_MOV, .int_operand=5, .char_operand="ebx"});
      vpasm_add_instruction(&program, (Instruction) {.type=INSTRUCTION_MOV, .int_operand=7, .char_operand="eax"});
      vpasm_add_instruction(&program, (Instruction) {.type=INSTRUCTION_HALT});
      
      vpasm_initialize_registers(&memory);
      
      vpasm_load_program(&memory, &program);
      vpasm_exec_program(&memory);
      
      vpasm_debug_print_registers(stdout, &memory);
      vpasm_free(&memory);

    } else {
      usage(program_name);
      fprintf(stderr, "[ERROR] Unknown flag %s\n", flag);
      exit(1);
    }
  }
  
  return 0;
}
