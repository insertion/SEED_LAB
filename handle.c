#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "handle.h"

#define DEBUG 1

char *fileNotExist =
  "<html><b>File does not exist!</b></html>";
char *noPermission = 
  "<html><b>Access denied: no permission!</b></html";


void handleHead (char *uri, int fd)
{
  // to do 
  return;
}

void handleGet (char *uri, int fd)
{
  char *path;
  char *info;
  
  assert (uri);
  fprintf (stderr, "uri=%s\n", uri);
  if (strcmp (uri, "/")==0)
    uri = "/index.html";
  path = malloc (strlen (uri)+3);
  strcpy (path, "./");
  strcpy (path+2, uri);
  if (DEBUG)
    fprintf (stderr, "#%s#", path);
  
  if (access(path, F_OK)!=0){
    fprintf (stderr, "file: %s not found\n"
	     , path);
    info = "HTTP/1.1 200 OK\r\n\r\n";
    write (fd, info, strlen(info));
    write (fd, fileNotExist, strlen (fileNotExist));
    return;
  }
  if (access(path, R_OK)!=0){
    fprintf (stderr, "file: %s no perm\n"
	     , path);
    info = "HTTP/1.1 200 OK\r\n\r\n";
    write (fd, info, strlen(info));
    write (fd, noPermission, strlen (noPermission));
    return;
  }
  fprintf (stderr, "file: %s OK\n"
	   , path);
  info = "HTTP/1.1 200 OK\r\n\r\n";
  write (fd, info, strlen(info));
  {
    char c;
    int file = open (path, O_RDONLY);
    while (read (file, &c, 1)){
      write (fd, &c, 1);
    }
    close (file);
  }
  return;
}

void Handle_main (int fd, Http_t tree)
{
  assert (tree);
  if (tree->kind != HTTP_KIND_REQUEST){
    fprintf (stderr, "server bug");
    close (fd);
    exit (0);
  }
  
  ReqLine_t reqline = tree->reqLine;
  assert (reqline);
  switch (reqline->kind){
  case REQ_KIND_GET:
    handleGet(reqline->uri, fd);
    break;
  case REQ_KIND_HEAD:
    handleHead (reqline->uri, fd);
    break;
  default:
    fprintf (stderr, "server bug");
    close (fd);
    exit (0);
    break;
  }
  
  return;
}
