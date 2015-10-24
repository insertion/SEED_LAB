#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#define HOST_PORT 8989
#define DEBUG 1
#define BUF_SIZE 1024

#define DIE(msg)\
  do{								\
    fprintf (stderr, "Error: %s:%d: %s\n", __FILE__, __LINE__, msg);	\
    exit (0);							\
  }while(0)							\

int main (int argc, char **argv)
{
  int sockfd, client_sockfd;
  int host_port;
  
  int yes;
  char buffer[BUF_SIZE];//socket缓冲区大小
  
  struct sockaddr_in host_addr, client_addr;

  host_port = HOST_PORT;
  if (argc>1)
    host_port = atoi(argv[1]);
  
  if ((sockfd = socket (PF_INET, SOCK_STREAM, 0))==-1){
    DIE("creating a socket");
  }
  
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    DIE("setting socket option SO_REUSEADDR");

  memset(&(host_addr), '\0', sizeof(host_addr)); // zero off the structure
  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(host_port);
  host_addr.sin_addr.s_addr = 0;

  if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
    DIE("binding to socket");
  
  if (listen(sockfd, 100) == -1)
    DIE("listening on socket");
  signal(SIGCHLD, SIG_IGN);
  while (1){
    int size;
    if ((client_sockfd = accept (sockfd, (struct sockaddr *)&client_addr, &size))==-1)
      DIE("accepting client connection");

    if (DEBUG)
      printf ("server: accepting a client from %s port %d\n",
	    (char*)  inet_ntoa (client_addr.sin_addr),
	      ntohs (client_addr.sin_port));

    int pid;
    if ((pid=fork())==0){// in child
      char client_fd_str[32] = {'\0'};
      char *child_name = "./httpd";
      char *child_argv[] = {child_name, 
			  client_fd_str, 0};
      sprintf (client_fd_str, "%d", client_sockfd);
      printf ("%s\n", client_fd_str);
      if (execve (child_name, child_argv, 0)==-1)
	DIE("execve");
    }
    else
      close(client_sockfd);
    
  }
  return 0;
}

