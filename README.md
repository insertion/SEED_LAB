#中科大软件学院信息安全实验

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
 

