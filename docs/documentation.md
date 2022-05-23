# Documentation
* [Main inatruction](https://github.com/morrigan-plus-plus/vpm/blob/master/docs/main_instructions.md)
  * mov
  * jmp
  * jz
  * halt
  * print
* [Arithmetics](https://github.com/morrigan-plus-plus/vpm/blob/master/docs/arithmetics.md)
  * sum
  * mult
  * div
  * sub

## Registers
  There is 4 registers for storing numbers :
  eax, ebx, ecx, edx. You can use mov for moving values into them.

## Entry point
  Evert program in vpasm will begin its execution
  at entry point, marked with %entry.
 
  Everything that belongs to entry point shpuld start with 4 spaces.

  If program doesnt have entry point it wont execute 
