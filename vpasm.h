#include<stdbool.h>

#ifndef VPASM_H_
#define VPASM_H_

typedef struct {
  size_t memory_size;
  int* eax;
  int* ebx;
} Memory;

typedef enum {
  INSTRUCTION_MOV,
} Instruction_Type;

typedef struct {
  Instruction_Type type;
  char* char_operand;
  int int_operand; 
} Instruction;

void vpasm_initialize_registers(Memory* memory);
void vpasm_free_registers(Memory* memory);

void vpasm_exec_inst(Memory* memory, Instruction instruction, bool trace);

void vpasm_debug_print_registers(FILE *stream, Memory* memory);

#endif //VPASM_H_
