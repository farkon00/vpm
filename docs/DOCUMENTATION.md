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

## Usage
USAGE: 
```
./vpm <flags> [arguments]

-r <input.vpasm> [-o output.vpm]   Compile vpasm file to a .vpm binary file and execute output file.
-v <input.vpasm> [-o output.vpm]   Compile vpasm file to a .vpm binary file.
-e <program.vpm>                   Execute a .vpm file
-h --help                          Display this help message.
```

## Registers
  There are 4 registers:
    eax, ebx, ecx, edx.
  You can use mov for moving values between them.

## Entry point
  Every program in vpasm begins at the entry point: %entry

  Everything that belongs to the entry point should be intented with 4 spaces.

  If program doesn't have entry point, it won't execute.
