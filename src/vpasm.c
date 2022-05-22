#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "vpasm.h"


#define REGISTERS 4
#define MAX_ARGS 2
#define MAX_ARG_LENGTH 4
#define cmp(string, other) strcmp(string, other) == 0

Instruction BUILD_INST(Instruction_Type type, size_t arg_count)
{
  return (Instruction) {
    .type = type,
    .arg_count = arg_count
  };
}

Instruction INST_MOV(char* reg, char* value) {
  Instruction inst = BUILD_INST(INSTRUCTION_MOV, 2);
  strncpy(inst.arguments[0], reg, 4);
  strncpy(inst.arguments[1], value, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_SUM(char* regOne, char* regTwo) {
  Instruction inst = BUILD_INST(INSTRUCTION_SUM, 2);
  strncpy(inst.arguments[0], regOne, 4);
  strncpy(inst.arguments[1], regTwo, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_SUB(char* regOne, char* regTwo) {
  Instruction inst = BUILD_INST(INSTRUCTION_SUB, 2);
  strncpy(inst.arguments[0], regOne, 4);
  strncpy(inst.arguments[1], regTwo, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_MULT(char* regOne, char* regTwo) {
  Instruction inst = BUILD_INST(INSTRUCTION_MULT, 2);
  strncpy(inst.arguments[0], regOne, 4);
  strncpy(inst.arguments[1], regTwo, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_DIV(char* regOne, char* regTwo) {
  Instruction inst = BUILD_INST(INSTRUCTION_DIV, 2);
  strncpy(inst.arguments[0], regOne, 4);
  strncpy(inst.arguments[1], regTwo, 4);
  assert(inst.arguments[0][3] == '\0' && inst.arguments[1][3] == '\0');
  return inst;
}
Instruction INST_JMP(char* jmpLoc) {
  Instruction inst = BUILD_INST(INSTRUCTION_JMP, 1);
  strncpy(inst.arguments[0], jmpLoc, 4);
  assert(inst.arguments[0][3] == '\0');
  return inst;
}
Instruction INST_JMP_IF_ZERO(char* jmpLoc) {
  Instruction inst = BUILD_INST(INSTRUCTION_JMP_IF_ZERO, 1);
  strncpy(inst.arguments[0], jmpLoc, 4);
  assert(inst.arguments[0][3] == '\0');
  return inst;
}
Instruction INST_DEBUG_PRINT(char* reg) {
  Instruction inst = BUILD_INST(INSTRUCTION_DEBUG_PRINT, 1);
  strncpy(inst.arguments[0], reg, 4);
  assert(inst.arguments[0][3] == '\0');
  return inst;
}
Instruction INST_HALT() {
  return (Instruction) {.type = INSTRUCTION_HALT};
}


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

void check_arg_amount(String_View instruction, String_View **arguments, size_t amount)
{
    for (size_t i = 0; i < amount; ++i) {
        if ((*arguments)[i].count <= 0) {
            fprintf(stderr, "[ERROR] Incorrect amount of arguments for instruction %s\n", sv_to_cstr(instruction));
            exit(1);
        }
    }
}

Instruction vpasm_text_to_inst(String_View instruction, String_View **arguments)
{
    if (cmp(sv_to_cstr(instruction), "mov")) {
        check_arg_amount(instruction, arguments, 2);
        return INST_MOV(sv_to_cstr((*arguments)[0]), sv_to_cstr((*arguments)[1]));
    } else if (cmp(sv_to_cstr(instruction), "print")) {
        check_arg_amount(instruction, arguments, 1);
        return INST_DEBUG_PRINT(sv_to_cstr((*arguments)[0]));
    } else if (cmp(sv_to_cstr(instruction), "halt")) {
        return INST_HALT();
    } else if (cmp(sv_to_cstr(instruction), "sum")) {
        check_arg_amount(instruction, arguments, 2);
        return INST_SUM(sv_to_cstr((*arguments)[0]), sv_to_cstr((*arguments)[1]));
    } else if (cmp(sv_to_cstr(instruction), "sub")) {
        check_arg_amount(instruction, arguments, 2);
        return INST_SUB(sv_to_cstr((*arguments)[0]), sv_to_cstr((*arguments)[1]));
    } else if (cmp(sv_to_cstr(instruction), "mult")) {
        check_arg_amount(instruction, arguments, 2);
        return INST_MULT(sv_to_cstr((*arguments)[0]), sv_to_cstr((*arguments)[1]));
    } else if (cmp(sv_to_cstr(instruction), "div")) {
        check_arg_amount(instruction, arguments, 2);
        return INST_DIV(sv_to_cstr((*arguments)[0]), sv_to_cstr((*arguments)[1]));
    } else if (cmp(sv_to_cstr(instruction), "jmp")) {
        check_arg_amount(instruction, arguments, 1);
        return INST_JMP(sv_to_cstr((*arguments)[0]));
    } else if (cmp(sv_to_cstr(instruction), "jz")) {
        check_arg_amount(instruction, arguments, 1);
        return INST_JMP_IF_ZERO(sv_to_cstr((*arguments)[0]));
    } else {
        fprintf(stderr, "[ERROR] Unrecognized instruction: %s\n", sv_to_cstr(instruction));
    }

    (void) arguments;
    return (Instruction) {0};
}

void vpasm_parse_file(Program* program, char* file_contents)
{

    (void) program;

    String_View program_sv = cstr_to_sv(file_contents);

    size_t entry = 0;

    while (program_sv.count > 0) {
        String_View line = sv_chop_by_delimiter(&program_sv, '\n');

        if (sv_cmp_cstr(sv_trim_whitespace(line), "%entry:") == 0) {
            if (entry == 1) {
                /* Already have an entry point, can't have two. */
                fprintf(stderr, "[ERROR] Encountered more than one %centry point.\n", 37);
            }
            entry = 1;
        }

        if (entry > 0) {
            line = sv_trim_whitespace(line);
            if (sv_cmp_cstr(line, "%entry:") != 0) {
                size_t argument_count = 0;
                String_View instruction = sv_chop_by_delimiter(&line, ' ');
                if (cmp(sv_to_cstr(sv_trim_whitespace(instruction)), "")) {
                    continue;
                }
                String_View* arguments = calloc(MAX_ARGS, sizeof(String_View));
                if (arguments == NULL) {
                    fprintf(stderr, "[ERROR] Error allocating memory for arguments of instruction %s\n", sv_to_cstr(instruction));
                    exit(1);
                }

                while (line.count > 0) {
                    assert(++argument_count <= MAX_ARGS && "[ERROR] Too many arguments.");

                    String_View argument = sv_chop_by_delimiter(&line, ' ');

                    assert(argument.count < MAX_ARG_LENGTH && "[ERROR] Argument too long.");

                    arguments[argument_count - 1] = argument;
                }

                Instruction inst = vpasm_text_to_inst(instruction, &arguments);

                vpasm_add_instruction(program, inst);
            }
        }
    }

    if (entry == 0) {
        fprintf(stderr, "[ERROR] No %%entry point found!");
    }
}


void vpasm_load_from_file(Program* program, char* file_path)
{
    FILE *f = fopen(file_path, "rb");

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    assert (fsize % sizeof(char) == 0);

    fseek(f, 0, SEEK_SET);

    char* file_contents = malloc(fsize + 1);

    fread(file_contents, sizeof(char), fsize / sizeof(char), f);

    fclose(f);

    if (file_contents == NULL) {
        fprintf(stderr, "[ERROR] Error reading file\n");
        exit(1);
    }

    vpasm_parse_file(program, file_contents);
}

void vpasm_load_program(Memory* memory, Program* program) {
  memory->program = malloc(sizeof(program) * PROGRAM_CAPACITY);
  *memory->program = *program;
}

void vpasm_exec_program(Memory* memory, size_t limit, bool trace)
{
  Program* program = memory->program;
  if (program == 0) {
    fprintf(stderr, "[ERROR] vpasm_exec_program: MEMORY HAS NO PROGRAM LOADED.\n");
    exit(1);
  } else {
    printf("Program Instruction Count: %zu\n", program->program_size);
    program->ip = 1;
    size_t current_exec = 0;
    while (program->ip < program->program_size && !program->halt && current_exec < limit) {
      ++current_exec;
      vpasm_exec_inst(memory, program->instructions[program->ip], trace);
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
    ++memory->program->ip;
    break;
  case INSTRUCTION_HALT:
    if (trace) printf("[TRACE] HALT\n");
    memory->program->halt = 1;
    break;
  case INSTRUCTION_SUM:
    {
    if (instruction.arg_count != 2) {
      fprintf(stderr, "[ERROR] SUM requires 2 arguments.");
      exit(1);
    }

    if (trace) printf("[TRACE] SUM %s %s\n", instruction.arguments[0], instruction.arguments[1]);

    size_t regOne = vpasm_reg_name_to_index(instruction.arguments[0]);
    size_t regTwo = vpasm_reg_name_to_index(instruction.arguments[1]);

    memory->registers[regOne] = memory->registers[regOne] + memory->registers[regTwo];
    }
    ++memory->program->ip;
    break;
  case INSTRUCTION_MULT:
    {
      if (instruction.arg_count != 2) {
	fprintf(stderr, "[ERROR] MULT requires 2 arguments.");
	exit(1);
      }

      if (trace) printf("[TRACE] MULT %s %s\n", instruction.arguments[0], instruction.arguments[1]);

      size_t regOne = vpasm_reg_name_to_index(instruction.arguments[0]);
      size_t regTwo = vpasm_reg_name_to_index(instruction.arguments[1]);

      memory->registers[regOne] = memory->registers[regOne] * memory->registers[regTwo];
    }
    ++memory->program->ip;
    break;
  case INSTRUCTION_DIV:
    {
      if (instruction.arg_count != 2) {
	fprintf(stderr, "[ERROR] DIV requires 2 arguments.");
	exit(1);
      }

      if (trace) printf("[TRACE] DIV %s %s\n", instruction.arguments[0], instruction.arguments[1]);

      size_t regOne = vpasm_reg_name_to_index(instruction.arguments[0]);
      size_t regTwo = vpasm_reg_name_to_index(instruction.arguments[1]);

      if (memory->registers[regTwo] == 0) {
	fprintf(stderr, "[ERROR] Cannot divide by 0.");
	exit(1);
      }

      memory->registers[regOne] = memory->registers[regOne] / memory->registers[regTwo];
    }
    ++memory->program->ip;
    break;
  case INSTRUCTION_SUB:
    {
    if (instruction.arg_count != 2) {
      fprintf(stderr, "[ERROR] SUB requires 2 arguments.");
      exit(1);
    }

    if (trace) printf("[TRACE] SUB %s %s\n", instruction.arguments[0], instruction.arguments[1]);

    size_t regOne = vpasm_reg_name_to_index(instruction.arguments[0]);
    size_t regTwo = vpasm_reg_name_to_index(instruction.arguments[1]);

    memory->registers[regOne] = memory->registers[regOne] - memory->registers[regTwo];

    }
    ++memory->program->ip;
    break;
  case INSTRUCTION_JMP:
    {
      if (instruction.arg_count != 1) {
	fprintf(stderr, "[ERROR] JMP requires 1 argument.");
	exit(1);
      }

      if (!isdigit(*instruction.arguments[0])) {
	fprintf(stderr, "[ERROR] %s is not a valid jump location.", instruction.arguments[0]);
	exit(1);
      }

      if (trace) printf("[TRACE] JMP %s\n", instruction.arguments[0]);

      memory->program->ip = atoi(instruction.arguments[0]);
      break;
    }
  case INSTRUCTION_JMP_IF_ZERO:
    {
      if (instruction.arg_count != 1) {
	fprintf(stderr, "[ERROR] JMP_IF_ZERO requires 1 argument.");
	exit(1);
      }

      if (!isdigit(*instruction.arguments[0])) {
	fprintf(stderr, "[ERROR] %s is not a valid jump location.", instruction.arguments[0]);
	exit(1);
      }

      if (trace) printf("[TRACE] JMP_IF_ZERO %s\n", instruction.arguments[0]);

      if (memory->registers[vpasm_reg_name_to_index("eax")] == 0) {
	memory->program->ip = atoi(instruction.arguments[0]);
      } else {
	++memory->program->ip;
      }
      break;
    }
  case INSTRUCTION_DEBUG_PRINT:
    {
    if (instruction.arg_count != 1) {
      fprintf(stderr, "[ERROR] DEBUG_PRINT requires 1 argument.");
      exit(1);
    }

    size_t reg = vpasm_reg_name_to_index(instruction.arguments[0]);

    printf("[DEBUG_PRINT] %s: %d\n", instruction.arguments[0], memory->registers[reg]);
    }
    ++memory->program->ip;
    break;
  default: assert(0 && "Unimplemented Instruction");
  }

}
