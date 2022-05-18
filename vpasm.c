#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include "vpasm.h"

#define MEM_CAPACITY 1024

void vpasm_initialize_registers(Memory* memory)
{
  memory->eax = malloc(sizeof(int));
  memory->ebx = malloc(sizeof(int));
}

void vpasm_free_registers(Memory* memory)
{
  free(memory->eax);
  free(memory->ebx);
}

void vpasm_debug_print_registers(FILE *stream, Memory* memory)
{
  fprintf(stream, "[DEBUG] vpasm_debug_print_registers:\n");
  fprintf(stream, "\tEAX: %d\n", *memory->eax);
  fprintf(stream, "\tEBX: %d\n", *memory->ebx);
}


void vpasm_exec_inst(Memory* memory, Instruction instruction, bool trace)
{

  (void) memory;
  (void) instruction;
  (void) trace;

  switch (instruction.type) {
  case INSTRUCTION_MOV:
    if (strcmp("eax", instruction.char_operand) == 0) {

      *memory->eax = instruction.int_operand;
      
    } else if (strcmp("ebx", instruction.char_operand) == 0) {

      *memory->ebx = instruction.int_operand;
      
    } else {
      fprintf(stderr, "[ERROR] Invalid argument for instruction MOV.");
    }
    break;
  default: break;
  }
  
}
