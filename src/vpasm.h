#include<stdbool.h>

#include "stringview.h"

#ifndef VPASM_H_
#define VPASM_H_

typedef enum {
  INSTRUCTION_MOV,
  INSTRUCTION_HALT,
  INSTRUCTION_SUM,
  INSTRUCTION_SUB,
  INSTRUCTION_JMP,
  INSTRUCTION_DEBUG_PRINT,
  INSTRUCTION_MULT,
  INSTRUCTION_DIV
} Instruction_Type;

typedef struct {
  Instruction_Type type;
  char** arguments;
  size_t arg_count;
} Instruction;

typedef struct {
  size_t ip;
  size_t halt;
  size_t program_size;
  Instruction* instructions;
} Program;

typedef struct {
  size_t memory_size;
  Program* program;
  int* registers;
} Memory;


char* vpasm_reg_index_to_name(size_t register_index);

void vpasm_add_instruction(Program* program, Instruction instruction);

void vpasm_initialize_registers(Memory* memory);
void vpasm_free(Memory* memory);

void vpasm_load_program(Memory* memory, Program* program);
void vpasm_exec_program(Memory* memory, size_t limit, bool trace);

void vpasm_exec_inst(Memory* memory, Instruction instruction, bool trace);

void vpasm_debug_print_registers(FILE *stream, Memory* memory);

#endif //VPASM_H_
