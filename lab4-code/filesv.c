#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "parse.h"
#include "http.h"
#include "handle.h"

#ifndef DEBUG
#define DEBUG 0
#endif

static void error (int fd, int errcode, char *msg);
static void parse(int fd);

// utilities
void die (const char *msg)
{
  fprintf (stderr, "Error: %s\n", msg);
  exit (0);
}

void kprint (const char *msg)
{
  write (1, msg, sizeof (msg));
  return;
}

void write_file (int sockfd, const char *s)
{
  int size = strlen (s);

  write (sockfd, s, size);
  return;
}

int main (int argc, char **argv)
{
  Http_t tree;

  if (argc<2)
    die ("server bug");

  signal(SIGCHLD, SIG_IGN);
  
  // get the pipe fd
  int pipefd = atoi (argv[1]);
  if (DEBUG)
    printf ("pipefd = %d\n", pipefd);

  while (1){
    char uri_str[1024];
    int sockfd;
   
    recvfd (pipefd, uri_str, sizeof(uri_str), &sockfd);
    if (DEBUG){
      printf ("filesv client recieves a sockfd = %d\n", sockfd);
      printf("uri = %s\n", uri_str);
    }

    if(fork() == 0){
      ReqLine_t reqline = ReqLine_new(REQ_KIND_GET
				      , uri_str
				      , HTTP_ONE_ONE);
      if (DEBUG)
	printf ("filesv parsing...\n");
      tree = Parse_parse(sockfd, 0);
      tree->reqLine = reqline;
      // response
      if (DEBUG)
	printf ("filesv responding...\n");
      Handle_main (sockfd, tree);
      
      close(sockfd);
      exit(0);
    }    
    close(sockfd);
  }

  return 0;
}

////////////////////////////////////////////
// parser
void error (int fd, int errCode, char *msg)
{
  int c;

  while(read(fd, &c, 1)!=-1)
    ;
  close (fd);
  
  fprintf (stderr, "%d\n", errCode);
  fprintf (stderr, "%s\n", msg);
  exit (0);
  return;
}

