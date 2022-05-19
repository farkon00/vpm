#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "./vpasm.h"

#define INST_MOV(reg, value) (Instruction) {.type = INSTRUCTION_MOV, .arguments = (char*[]){reg, value}, .arg_count = 2}
#define INST_SUM(regOne, regTwo) (Instruction) {.type = INSTRUCTION_SUM, .arguments = (char*[]){regOne, regTwo}, .arg_count = 2}
#define INST_SUB(regOne, regTwo) (Instruction) {.type = INSTRUCTION_SUB, .arguments = (char*[]){regOne, regTwo}, .arg_count = 2}
#define INST_MULT(regOne, regTwo) (Instruction) {.type = INSTRUCTION_MULT, .arguments = (char*[]){regOne, regTwo}, .arg_count = 2}
#define INST_DIV(regOne, regTwo) (Instruction) {.type = INSTRUCTION_DIV, .arguments = (char*[]){regOne, regTwo}, .arg_count = 2}
#define INST_JMP(jmpLoc) (Instruction) {.type = INSTRUCTION_JMP, .arguments = (char*[]){jmpLoc}, .arg_count = 1}
#define INST_JMP_IF_ZERO(jmpLoc) (Instruction) {.type = INSTRUCTION_JMP_IF_ZERO, .arguments = (char*[]){jmpLoc}, .arg_count = 1}
#define INST_DEBUG_PRINT(reg) (Instruction) {.type = INSTRUCTION_DEBUG_PRINT, .arguments = (char*[]){reg}, .arg_count = 1}
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

    vpasm_add_instruction(&program, INST_MOV("eax", "10"));
    vpasm_add_instruction(&program, INST_MOV("ebx", "0"));
    vpasm_add_instruction(&program, INST_MOV("ecx", "1"));
    vpasm_add_instruction(&program, INST_DEBUG_PRINT("ebx"));
    vpasm_add_instruction(&program, INST_DEBUG_PRINT("ecx"));
    vpasm_add_instruction(&program, INST_MOV("edx", "2"));
    vpasm_add_instruction(&program, INST_SUB("eax", "edx"));
    vpasm_add_instruction(&program, INST_SUM("ebx", "ecx"));
    vpasm_add_instruction(&program, INST_SUM("ecx", "ebx"));
    vpasm_add_instruction(&program, INST_DEBUG_PRINT("ebx"));
    vpasm_add_instruction(&program, INST_DEBUG_PRINT("ecx"));
    vpasm_add_instruction(&program, INST_SUB("eax", "edx"));
    vpasm_add_instruction(&program, INST_JMP_IF_ZERO("16"));
    vpasm_add_instruction(&program, INST_JMP("8"));
    vpasm_add_instruction(&program, INST_HALT);
      
    vpasm_initialize_registers(&memory);
      
    vpasm_load_program(&memory, &program);
    vpasm_exec_program(&memory, 100, false);
      
    vpasm_debug_print_registers(stdout, &memory);
    vpasm_free(&memory);
  } else {
    assert(0 && "Unreachable Code - vpm.c");
  }
  
  return 0;
}
