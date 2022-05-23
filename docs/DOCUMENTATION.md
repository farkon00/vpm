# Documentation
* [Main Instructions](https://github.com/morrigan-plus-plus/vpm/blob/master/docs/main_instructions.md)
  * mov
  * jmp
  * jz
  * halt
  * print
* [Arithmetical Instructions](https://github.com/morrigan-plus-plus/vpm/blob/master/docs/arithmetics.md)
  * sum
  * mult
  * div
  * sub

## Registers
  There are 4 registers:
    eax, ebx, ecx, edx.
  You can use mov for moving values between them.

## Entry point
  Every program in vpasm begins at the entry point: %entry

  Everything that belongs to the entry point should be intented with 4 spaces.

  If program doesn't have entry point, it won't execute.
