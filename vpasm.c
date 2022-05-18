#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#include "vpasm.h"

#define MEM_CAPACITY 1024

void vpasm_initialize_memory(Memory* memory)
{
  memory->memory = malloc(MEM_CAPACITY * sizeof(int)); 
}

void vpasm_free_memory(Memory* memory)
{
  free(memory->memory);
}

void vpasm_debug_print_memory(FILE *stream, Memory* memory)
{
  fprintf(stream, "[DEBUG] vpasm_debug_print_memory:\n");
  for (size_t i = 1; i <= memory->memory_size; ++i) {
    fprintf(stream, "    Position %zu: %d\n", i, *(memory->memory + (i)));
  }
}

void vpasm_exec_inst(Memory* memory, char* instruction, bool trace)
{
  if (strcmp("push", instruction) == 0) {
    if (trace) printf("PUSHING 60:\n");
    assert(memory->memory_size < MEM_CAPACITY);
    memory->memory[++memory->memory_size] = 60;
    if (trace) printf("    Current mem size: %zu. Position %zu has value %d\n", memory->memory_size, memory->memory_size, memory->memory[memory->memory_size]);
  } else {
    fprintf(stderr, "vpasm_exec_inst: UNREACHABLE");
    exit(1);
  }

}
