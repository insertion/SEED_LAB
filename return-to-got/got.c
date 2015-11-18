#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
	char *pointer=NULL;
	char array[10];
	pointer = array;
	strcpy(pointer,argv[1]);
	printf("array contains %s at %p\n",pointer,&pointer);

    /*通过修改printf@got来执行system函数
	got中存放了动态加载的库函数的绝对地址*/
	strcpy(pointer,argv[2]);
	printf("/bin/sh");
	return 0;
}
	
