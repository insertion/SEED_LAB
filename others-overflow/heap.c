#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define BUFFSIZE 16
#define OVERSIZE 8

int main()
{
	unsigned long diff;
	char *buff1= (char *)malloc(BUFFSIZE);
	char *buff2= (char *)malloc(BUFFSIZE);

	diff=(unsigned long)buff2-(unsigned long)buff1;
	printf(">buff1 =%p,buff2 =%p,diff =%d bytes\n",buff1,buff2,(int)diff);

	memset(buff2,'A',BUFFSIZE-1);
	buff2[BUFFSIZE-1]='\0';
	printf(">before overflow buff2 is :%s\n",buff2);

	memset(buff1,'B',diff+OVERSIZE);
	printf(">after overflow buff2 is :%s\n",buff2);
return 0;
}
