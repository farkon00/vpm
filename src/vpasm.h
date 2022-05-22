#include<stdbool.h>

#include "stringview.h"

#ifndef VPASM_H_
#define VPASM_H_


#define PROGRAM_CAPACITY 1024

typedef enum {
  INSTRUCTION_MOV, // MOV <register 1> <register 2 / value> - Moves the value of register 2 or an immediate value into register 1
  INSTRUCTION_HALT, // HALT - Halts the program
  INSTRUCTION_SUM, // SUM <register 1> <register 2> - Sums the value of the two registers and stores it in register 1
  INSTRUCTION_SUB, // SUB <register 1> <register 2> - Subtracts the value of register 2 from register 1 and stores it in register 1
  INSTRUCTION_JMP, // JMP <instruction> - Jumps to a specific instruction
  INSTRUCTION_DEBUG_PRINT, // DEBUG_PRINT <register> - Prints a register's value for debug purposes
  INSTRUCTION_MULT, // MULT <register 1> <register 2> - Multiplies the value of the two registers and stores it in register 1
  INSTRUCTION_DIV, // DIV <register 1> <register 2> - Divides the value of register 1 by register 2 and stores it in register 1, so long as register 2 is not 0
  INSTRUCTION_JMP_IF_ZERO // JMP_IF_ZERO <instruction> - Jumps to a specific instruction so long as `eax` is 0
} Instruction_Type;

typedef struct {
  Instruction_Type type;
  char arguments[2][4];
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

void vpasm_load_from_file(Program* program, char* file_path);

void vpasm_load_program(Memory* memory, Program* program);
void vpasm_exec_program(Memory* memory, size_t limit, bool trace);

void vpasm_exec_inst(Memory* memory, Instruction instruction, bool trace);

void vpasm_debug_print_registers(FILE *stream, Memory* memory);

#endif //VPASM_H_
