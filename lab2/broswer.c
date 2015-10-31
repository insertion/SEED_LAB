#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>

#define PORT  8080

/*
** construct your shellcode
**create_shellcode.c will help you to create a shellcode.
**fill in it there	 

  const char shellcode[] = ;
  
*/

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
  
  /*
    below show that client send a normal request to the web server
    you should fix the code to realize your attack
  */  
  char *req ="GET / HTTP/1.1\r\n\r\n";
  write(sock_client,req,strlen(req));
  
  //receive the response from web server
  char resp[1024];
  int num = 0;
  while(read (sock_client, &resp[num], 1))
	num++;
  resp[num] = 0;
  printf("Response = %s\n",resp);
  
  close(sock_client);
  
 
 return 0;
}
