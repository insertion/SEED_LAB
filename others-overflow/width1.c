#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char *argv[])
{
	unsigned short s;
	int i;
	char buf[80];

	if(argc<3)
	{
		printf("there needs 2 args");
		return -1;
	}
	
	i= atoi(argv[1]);
	s=i;
	
	if(s>=80)
	{
		printf("oh no !\n");
	}
	printf("s = %d\n",s);
	
	memcpy(buf,argv[2],s);
	printf("i = %d\n",i);
	buf[s]='\0';
	printf("the string is :%s\n",buf);
	return 0;
}
