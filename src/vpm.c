#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "./vpasm.h"

#define INST_MOV(reg, value) (Instruction) {.type = INSTRUCTION_MOV, .arguments = (char*[]){reg, value}, .arg_count = 2}
#define INST_SUM(regOne, regTwo) (Instruction) {.type = INSTRUCTION_SUM, .arguments = (char*[]){regOne, regTwo}, .arg_count = 2}
#define INST_SUB(regOne, regTwo) (Instruction) {.type = INSTRUCTION_SUB, .arguments = (char*[]){regOne, regTwo}, .arg_count = 2}
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

  printf("%s\n", sv_to_cstr(sv_trim_whitespace(cstr_to_sv("   [TEST] String_Views functioning correctly!    "))));
  
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

    // MOV eax 5
    // MOV ebx 10
    // SUM eax ebx (adds 10 to 5, leaving 15 in eax)
    // MOV ebx 15
    // SUB eax ebx (subtracts 15 from 15, zeroing eax)

    // EXPECTED:
    // rax: 0
    // rbx: 15

    vpasm_add_instruction(&program, INST_MOV("eax", "5"));
    vpasm_add_instruction(&program, INST_MOV("ebx", "10"));
    vpasm_add_instruction(&program, INST_SUM("eax", "ebx"));
    vpasm_add_instruction(&program, INST_MOV("ebx", "15"));
    vpasm_add_instruction(&program, INST_SUB("eax", "ebx"));
    vpasm_add_instruction(&program, INST_HALT);
      
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
