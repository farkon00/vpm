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


void vpasm_exec_inst(Memory* memory, char* instruction, bool trace)
{
  (void) instruction;

  if (strcmp("mov", instruction) == 0) {
    // Hard coded for testing
    // mov eax 2
    if (trace) printf("Executing:\n\tMOV EAX 2\n");
    *memory->eax = 2;
  }
  
}
