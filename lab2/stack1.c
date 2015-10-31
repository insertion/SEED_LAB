#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void badman()
{
    printf("I am the bad man\n");
    return;
}

int func(char *str)
{
  int variable_a;
  char buffer[12];
  /* Fill in code here to print the address of
   * the array "buffer".
   * Your code here:
   */

  strcpy(buffer, str);
  
  return 1;
}

int main(int argc, char **argv)
{
  char *buf = "hello\n";
  
  if(argc > 1){
    buf = argv[1];
  }

  func(buf);
  printf("Returned Properly\n");
  return 1;
}
