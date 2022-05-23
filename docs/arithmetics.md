# Documentation
## Arithmetics
* [sum](#sum)
* [mult](#mult)
* [div](#div)
* [sub](#sub)

## sum
  Syntax: `sum <register> <register>`

  Sums the values of two registers and stores the result in the first register given.

  Examples:
  ```
  mov eax 1
  mov ebx 2
  sum eax ebx
  ```

## mult
  Syntax: `mult <register> <register>`

  Multiplies the values of two registers and stores the result in the first register given.

  Examples:
  ```
  mov eax 2
  mov ebx 2
  mult eax ebx
  ```

## div
  Syntax: `div <register> <register>`

  Divides* the values of two registers and stores the result in the first register given.
  If division by zero is attempted, an error will be thrown.

  * This is integer division

  Examples:
  ```
  mov eax 4
  mov ebx 2
  div eax ebx
  ```

## sub
  Syntax: `sub <register> <register>`

  Subtracts the values of the second register from the first and stores the result in the first register given.

  Examples:
  ```
  mov eax 4
  mov ebx 2
  sub eax ebx
  ```
