#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
  char* helloWorld = malloc(15);
  strcpy(helloWorld, "Hello, world!\n");
 
  printf("%s", helloWorld);

  free(helloWorld);
  return 0;
}
