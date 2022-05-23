# Documentation
## Arithmetics
* [sum](#sum)
* [mult](#mult)
* [div](#div)
* [sub](#sub)

## sum
  Syntax : `sum <register> <register>`

  Sums values of two registers and writes result into first register given.

  Examples :
  ```
  mov eax 1
  mov ebx 2
  sum eax ebx
  ```

## mult
  Syntax : `mult <register> <register>`

  Multiplies values of two registers and writes result into first register given.

  Examples :
  ```
  mov eax 2
  mov ebx 2
  mult eax ebx
  ```

## div
  Syntax : `div <register> <register>`

  Divides value of first register by second one and
  writes result into first register given. On division
  by zero throw an error. This is integer division.

  Examples :
  ```
  mov eax 4
  mov ebx 2
  div eax ebx
  ```

## sub
  Syntax : `sub <register> <register>`

  Subtructs value of second register from first one and
  writes result into first register given.

  Examples :
  ```
  mov eax 4
  mov ebx 2
  sub eax ebx
  ```
