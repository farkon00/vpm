#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "vpasm.h"

#define PROGRAM_CAPACITY 1024
#define REGISTERS 4

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
  memory->registers = malloc(sizeof(char*) * REGISTERS);
}

void vpasm_free(Memory* memory)
{
  free(memory->registers);
  free(memory->program->instructions);
  free(memory->program);
}

char* vpasm_reg_index_to_text(size_t register_index) {
  switch (register_index) {
  case 0:
    return "eax";
  case 1:
    return "ebx";
  case 2:
    return "ecx";
  case 3:
    return "edx";
  default:
    assert(0 && "Invalid register location");
  }
}
size_t vpasm_reg_name_to_index(char* name) {
  if (strcmp(name, "eax") == 0) {
    return 0;
  } else if (strcmp(name, "ebx") == 0) {
    return 1;
  } else if (strcmp(name, "ecx") == 0) {
    return 2;
  } else if (strcmp(name, "edx") == 0) {
    return 3;
  } else {
    fprintf(stderr, "[ERROR] Invalid Register Name: %s\n", name);
    exit(1);
  }
}

void vpasm_load_program(Memory* memory, Program* program) {
  /* TODO */
  memory->program = malloc(sizeof(program) * PROGRAM_CAPACITY);
  *memory->program = *program;
}

void vpasm_exec_program(Memory* memory)
{
  Program* program = memory->program;
  if (program == 0) {
    fprintf(stderr, "[ERROR] vpasm_exec_program: MEMORY HAS NO PROGRAM LOADED.\n");
    exit(1);
  } else {
    printf("Program Instruction Count: %zu\n", program->program_size);
    while (program->ip < program->program_size && !program->halt) {
      vpasm_exec_inst(memory, program->instructions[++program->ip], true);
    }
  }
}

void vpasm_debug_print_registers(FILE *stream, Memory* memory)
{
  fprintf(stream, "[DEBUG] vpasm_debug_print_registers:\n");
  for (size_t i = 0; i < REGISTERS; ++i) {
    fprintf(stream, "%s: %d\n", vpasm_reg_index_to_text(i), memory->registers[i]);
  }
}


void vpasm_exec_inst(Memory* memory, Instruction instruction, bool trace)
{
  (void) trace;
  switch (instruction.type) {
  case INSTRUCTION_MOV:
    if (instruction.arg_count != 2) {
      fprintf(stderr, "[ERROR] MOV requires 2 arguments.");
      exit(1);
    }

    if (trace) printf("[TRACE] MOV %s %s\n", instruction.arguments[0], instruction.arguments[1]);
    
    if (isdigit(*instruction.arguments[0])) {
	/* Invalid for first instruction */
	fprintf(stderr, "[ERROR] Cannot move to a value.");
	exit(1);
    }
      
    size_t reg = vpasm_reg_name_to_index(instruction.arguments[0]);

    if (!isdigit(*instruction.arguments[1])) {
      // Register?
      size_t register_index = vpasm_reg_name_to_index(instruction.arguments[1]);
      memory->registers[reg] = memory->registers[register_index];
    } else {
      memory->registers[reg] = atoi(instruction.arguments[1]);
    }
    
    break;
  case INSTRUCTION_HALT:
    if (trace) printf("[TRACE] HALT\n");
    memory->program->halt = 1;
    break;
  default: assert(0 && "Unimplemented Instruction");
  }
  
}
