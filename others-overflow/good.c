#include<stdio.h>
int main()
{
	int flag =0;
	int *p = &flag;
	char a[100];
	scanf("%s",a);
	printf(a);
	if(flag == 2000)
	{
		printf("good!\n");
	}
}
