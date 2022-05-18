#include<stdbool.h>

#ifndef VPASM_H_
#define VPASM_H_

typedef struct {
  size_t memory_size;
  int* memory;
} Memory;

void vpasm_initialize_memory(Memory* memory);
void vpasm_free_memory(Memory* memory);

void vpasm_exec_inst(Memory* memory, char* instruction, bool trace);

void vpasm_debug_print_memory(FILE *stream, Memory* memory);

#endif //VPASM_H_
