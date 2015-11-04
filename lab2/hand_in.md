#lab2实验报告

* **练习1**: 开启no-execute stack后无法再像lab1中一样进行缓冲区溢出攻击，在栈中的shellcode无法执行
* **练习2**: 如图一所示，![图一](http://img-storage.qiniudn.com/15-11-4/81520266.jpg)通过往ret中填入库函数system的地址，并在其上方填入参数‘ls’的地址，这样在fun返回后就通过system执行ls。其崩溃的原因是在system结束后，不知返回到哪。经过修改，在system的ret处填入exit的地址，程序可以正常退出。
* **练习3**: 通过return-to-libc攻击./touchstone 结果如图二![](http://img-storage.qiniudn.com/15-11-4/92775404.jpg)所示。成功通过system产生一个bash。
* **练习4**: 开启ASLR后，不能正常攻击，因为libc库和栈的地址都被随机化了，我们不能预先直到其内存地址
* **练习5**: 暴力破解ASLR,system,exit,和在libc.so中找到的字符串"/bin/sh"（作为system的参数）。经实验发现，它们三个在内存中的相对地址使不变的，所以我们只需要穷举system的可能地址，就可以直到另外两个的地址。在实验过程中发现，system的地址前两位和后三位使不变的，只有中间三位是随机的，所以我们可以利用`for(addr=0xb7000060;addr<=0xb7fff060;addr=addr+0x00001000)`来穷举system的地址。实验结果如图三![](http://img-storage.qiniudn.com/15-11-4/64600592.jpg)所示，我们成功的产生了一个进程shell。 