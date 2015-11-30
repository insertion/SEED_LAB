#中科大软件学院信息安全实验

## [lab2](https://github.com/insertion/SEED_LAB/blob/master/lab2/hand_in.md#lab2%E5%AE%9E%E9%AA%8C%E6%8A%A5%E5%91%8A) OVER！

![](http://img-storage.qiniudn.com/15-11-4/79440814.jpg)


参考文献
* [栈与函数调用惯例](http://blog.csdn.net/xiaogugood/article/details/38490663)  
* [Blind Return Oriented Programming  Attack](http://drops.wooyun.org/tips/3071)
* [一步步学习ROP](http://drops.wooyun.org/tips/6597)
* [linux 下动态链接](http://jzhihui.iteye.com/blog/1447570)

##lab1:缓冲区溢出

 关于socket和HTTP协议

##lab2:Return-to-libc

**libc.so中函数的相对偏移地址是固定的，对system穷举，就可以顺带知道exit，参数“/bin/sh”的地址**

> gdb file 和gdb file core 查看的内存空间是不一样的，gdb file查看的是gdb fork出来的子进程的内存空间，
> gdb core查看的是file在shell中实际运行时的内存空间
> 所以通过gdb file找出来的“/bin/bash”地址，在实际运行中并不是/bin/bash
 
## lab3: 权限分离

nothing to say

