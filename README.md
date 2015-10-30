#中科大软件学院信息安全实验

参考文献
* [栈与函数调用惯例](http://blog.csdn.net/xiaogugood/article/details/38490663)  ---------------------------*加深对缓冲区溢出的理解*
* [x86下的C函数调用惯例](http://blog.csdn.net/phunxm/article/details/8985321)

##lab1:缓冲区溢出

####exercise1
 添加的代码如下
``` c
printf("0x%x",buffer)
```
> 因为内存随机化，所以每次输出的buffer地址都不一样

####exercise3
```
sudo sysctl -w kernel.randomize_va_space=0
```

> 关闭了内存随机化，每次输出结果都一样

####exercise5

> 通过gdb修改内存地址，跳转到`badman`,因为badman不是正常的函数调用，所以函数结束后不知道返回到哪即下一条指令，所以要在badman里面加一个`exit()`程序才能正确结束

####exercise6

> 通过gdb调试可知函数的返回地址存放在距离buffer 144byte的地方代码如下
```c
int *ret;
ret=(int)buffer+144;
*ret=buffer;
```

####exercise7

> 漏洞在parse.c的getToken函数中，通过对s[1024]数组的溢出可以攻击服务器

####exercise8

> 浏览器代码如下
```c
略
```

####exercise9

> 在parse.c 154行添加了如下代码

```c
if(i>=1024) return;
```

##lab2:Return-to-libc
> gdb file 和gdb file core 查看的内存空间是不一样的，gdb file查看的是gdb fork出来的子进程的内存空间，
> gdb core查看的是file在shell中实际运行时的内存空间
> 所以通过gdb file找出来的“/bin/bash”地址，在实际运行中并不是/bin/bash
 

