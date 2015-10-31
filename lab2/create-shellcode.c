#include <stdio.h>
#include <unistd.h>
#include  <stdlib.h>
#include <fcntl.h>

extern int mystart;
extern int end;

int main (int argc, char **argv)
{
  char s[3] = "\\x";
  //s[2] = 0; 
  
  char shell[2048];
  unsigned char *p = (unsigned char *)(&mystart);
  int i = 0;
  while(p < ( unsigned char *)(&end))
    {
      sprintf(shell+i*4,"%s",s);
      sprintf(shell+i*4+2,"%02x",*p);	 
      p++;	
      i++;
    }
  
  printf("shell code bytes  = %d\n",i);
  printf("%s\n", shell);
  
  
  
  __asm__("call end");
  /*
   * below sample shellcode is to unlink("/home/jianglei/a.txt") 
   * and exit(0) 
   */
   
  //write down your shellcode,note that you must end up with '\n' for each instruction
  
  __asm__(".globl mystart\n" 
	  "mystart:\n"
	  
	  "xor    %eax,%eax\n"      /* \x31\xc0    */
	  "push   %eax\n"           /* \x50        */
	  "push   $0x7478742e\n"    /* \x68 ".txt" */
	  "push   $0x612f6965\n"    /* \x68 "ei/a" */
	  "push   $0x6c676e61\n"    /* \x68 "angl" */
	  "push   $0x696a2f65\n"    /* \x68 "e/ji" */
	  "push   $0x6d6f682f\n"    /* \x68 "/home"*/
	  "mov    %esp,%ebx\n"      
	  "mov    $0xa,%al\n"
	  "int    $0x80\n"
	  "xor	%ebx,%ebx\n"
	  "mov    $0x1,%al\n"
	  "int    $0x80\n"
	  ".globl end\n"
	  "end:\n"
	  "leave\n"
	  "ret\n"
	  );
  
  return 0;
  
}

