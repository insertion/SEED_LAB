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
  
  #define len 1100  
  char req[len];
  memset(req,'A',len);
  req[len-4]='\r',
  req[len-3]='\n',
  req[len-2]='\r',
  req[len-1]='\n';
  //consruct your hack code here
  //but remember to keep the last 4 Byte unchanged.

  printf("[!!!]Implement your code here %s function: %s line: %d\n",__FILE__,__FUNCTION__,__LINE__);
  exit(-1);  

  write(sock_client,req,len);
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
