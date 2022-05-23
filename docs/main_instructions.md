# Documentation
## Main Instructions
* [mov](#mov)
* [jmp](#jmp)
* [jz](#jz)
* [halt](#halt)
* [print](#print)

## mov
  Syntax: `mov <register> <value | register>`

  Sets value of a register to the value of another
  or an immediate value.

  Examples:
  ```
  mov eax 1
  mov ebx eax
  ```

## jmp
  Syntax: `jmp <ip>`

  Unconditionally jumps to instruction with ip `ip`

  Examples:
  ```
  mov eax 1
  jmp 0
  ```

## jz
  Syntax: `jz <ip>`

  Jumps to instruction with ip `ip` if eax is zero.

  Examples:
  ```
  mov eax 1
  jmp 0
  ```

## halt
  Syntax: `halt`

  Simply stops execution of the program.

  Examples:
  ```
  mov eax 1
  halt
  ```

## print
  Syntax: `print <register>`

  [DEBUG ONLY] Prints register name and its value.

  Examples:
  ```
  mov eax 1
  print eax
  ```
