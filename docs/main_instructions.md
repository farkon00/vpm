# Documentation
## Main Instructions
* [mov](#mov)
* [jmp](#jmp)
* [jz](#jz)
* [halt](#halt)
* [print](#print)

## mov
  Syntax : `mov <register> <value | register>`

  Sets value of register in argument 1 to value of
  register in second argument or value in second
  register.

  Examples :
  ```
  mov eax 1
  mov ebx eax
  ```
  
## jmp
  Syntax : `jmp <ip>`

  Unconditionally jumps to insruction with ip `ip`

  Examples :
  ```
  mov eax 1
  jmp 0
  ```
  
## jz
  Syntax : `jz <ip>`

  Jumps to insruction with ip `ip` if eax is zero.

  Examples :
  ```
  mov eax 1
  jmp 0
  ```

## halt
  Syntax : `halt`

  Stops execution, doesnt take sny arguments.

  Examples :
  ```
  mov eax 1
  halt
  ```

## print
  Syntax : `print <register>`

  Used for debug, prints register name and its value.

  Examples :
  ```
  mov eax 1
  print eax
  ```