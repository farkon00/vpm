#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "./vpasm.h"

#define INST_MOV(reg, value) (Instruction){.type = INSTRUCTION_MOV, .char_operand=reg, .int_operand=value}
#define INST_HALT (Instruction){.type = INSTRUCTION_HALT}

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
  
  size_t exec = 0;
  while (argc > 0) {
    const char* flag = shift(&argc, &argv);
    
    if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0) {
      usage(program_name);
      exit(0);
    } else if (strcmp(flag, "-v") == 0) {
      exec = 1;
    } else {
      usage(program_name);
      fprintf(stderr, "[ERROR] Unknown flag %s\n", flag);
      exit(1);
    }
  }

  if (exec) {
    Memory memory = {0};
    Program program = {0};

    vpasm_add_instruction(&program, INST_MOV("ebx", 5));
    vpasm_add_instruction(&program, INST_MOV("eax", 7));
    vpasm_add_instruction(&program, INST_HALT);
    vpasm_add_instruction(&program, INST_MOV("ebx", 8));
      
    vpasm_initialize_registers(&memory);
      
    vpasm_load_program(&memory, &program);
    vpasm_exec_program(&memory);
      
    vpasm_debug_print_registers(stdout, &memory);
    vpasm_free(&memory);
  } else {
    assert(0 && "Unreachable Code - vpm.c");
  }
  
  return 0;
}
