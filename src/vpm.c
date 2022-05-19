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
Instruction INST_JMP(char* jmpLoc) { return (Instruction) {.type = INSTRUCTION_JMP, .arguments = (char[2][4]){jmpLoc}, .arg_count = 1};}
Instruction INST_JMP_IF_ZERO(char* jmpLoc) { return (Instruction) {.type = INSTRUCTION_JMP_IF_ZERO, .arguments = (char[2][4]){jmpLoc}, .arg_count = 1};}
Instruction INST_DEBUG_PRINT(char* reg) { return (Instruction) {.type = INSTRUCTION_DEBUG_PRINT, .arguments = (char[2][4]){reg}, .arg_count = 1};}
Instruction INST_HALT { return (Instruction) {.type = INSTRUCTION_HALT}

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

void program_as_bin_file(Program* program, char* output_file)
{
  FILE *f = fopen(output_file, "wb");
  if (f == NULL) {
    fprintf(stderr, "[ERROR] Could not open file `%s`\n", output_file);
    exit(1);
  }

  fwrite(program->instructions + 1, sizeof(Instruction), program->program_size, f);

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
  
  // TODO: Arguments aren't being read properly and it's causing SEGFAULT
  
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

    /* program_from_bin_file(&program, "output.vpm"); */

    /* for (size_t i = 1; i < program.program_size; ++i) { */
    /*   printf("a: %zu - %d\n", program.instructions[i].arg_count, program.instructions[i].type); */
    /*   if (program.instructions[i].arg_count > 1) { */
    /* 	printf("%zu\n", program.program_size); */
    /*   } */
    /* } */
    
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

    /* program_as_bin_file(&program, "output.vpm"); */
    
    vpasm_debug_print_registers(stdout, &memory);
    vpasm_free(&memory);
  } else {
    assert(0 && "Unreachable Code - vpm.c");
  }
  
  return 0;
}
