#include<stdbool.h>

#ifndef VPASM_H_
#define VPASM_H_

typedef enum {
  INSTRUCTION_MOV,
  INSTRUCTION_HALT,
} Instruction_Type;

typedef struct {
  Instruction_Type type;
  char* char_operand;
  int int_operand; 
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
  int* eax;
  int* ebx;
} Memory;


void vpasm_add_instruction(Program* program, Instruction instruction);

void vpasm_initialize_registers(Memory* memory);
void vpasm_free(Memory* memory);

void vpasm_load_program(Memory* memory, Program* program);
void vpasm_exec_program(Memory* memory);

void vpasm_exec_inst(Memory* memory, Instruction instruction, bool trace);

void vpasm_debug_print_registers(FILE *stream, Memory* memory);

#endif //VPASM_H_
