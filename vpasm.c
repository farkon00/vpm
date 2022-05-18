#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include "vpasm.h"

#define PROGRAM_CAPACITY 1024

void vpasm_add_instruction(Program* program, Instruction instruction)
{
  (void) instruction;
  
  if (program->instructions == 0) {
    program->instructions = malloc(PROGRAM_CAPACITY * sizeof(Instruction));
  }
  
  program->instructions[++program->program_size] = instruction;
}

void vpasm_initialize_registers(Memory* memory)
{
  memory->eax = malloc(sizeof(int));
  memory->ebx = malloc(sizeof(int));
}

void vpasm_free(Memory* memory)
{
  free(memory->eax);
  free(memory->ebx);
  free(memory->program->instructions);
  free(memory->program);
}

void vpasm_load_program(Memory* memory, Program* program) {
  /* TODO */
  memory->program = malloc(sizeof(program));
  *memory->program = *program;
}

void vpasm_exec_program(Memory* memory)
{
  const Program* program = memory->program;
  if (program == 0) {
    fprintf(stderr, "[ERROR] vpasm_exec_program: MEMORY HAS NO PROGRAM LOADED.\n");
    exit(1);
  } else {
    printf("Program Instruction Count: %zu\n", program->program_size);
    for (size_t i = 1; i <= program->program_size; ++i) {
      vpasm_exec_inst(memory, program->instructions[i], true);
    }
  }
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
