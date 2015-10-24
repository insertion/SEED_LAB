#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

#define DEBUG 1

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
  int sockfd;
  Http_t tree;

  if (argc<2)
    die ("server bug");

  sockfd = atoi (argv[1]);
  if (DEBUG)
    printf ("the sockfd is %d\n", sockfd);

  // parse the http requst
  tree = Parse_parse(sockfd);

  if (DEBUG){
    printf ("parse success"
	    "the http tree is:\n");
  }

  // response
  Handle_main (sockfd, tree);
  
  close(sockfd);
  printf("socked closed..");

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

