#include<stdio.h>
int main()
{
	int l=0xdeadbeef;
	short s=0xdeadbeaf;
	unsigned char c= 257;

	printf("l = 0x%x (%d bit)\n",l,sizeof(l) * 8);
	printf("s = 0x%x (%d bit)\n",s,sizeof(s) * 8);
	printf("c = 0x%x (%d bit)\n",c,sizeof(c) * 8);
	return 0;

}
/* EOF */
