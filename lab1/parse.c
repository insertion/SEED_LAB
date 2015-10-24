#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "token.h"

#define DEBUG 1

enum {A_NONE, A_SPACE, A_CRLF} ahead = A_NONE;

struct Token_t token = {-1, 0};

Http_t http400 = 0;
Http_t generate400();

int i = 0;
int n;
char c;
// prototypes
void advance (int fd, int sepBySpace);
char *eatToken (enum TokenKind_t, int, int);

char getChar (int fd)
{
  int n;
  char c;
  char *info;

  n = read (fd, &c, 1);
  switch (n){
  case -1:
    info = "fail to read the socket\n";
    write (1, info, strlen (info));
    Http_print (fd, http400);
    close (fd);
    exit (0);
    break;
  case 0: // socket is blocked
    info = "read 0 char\n";
    write (1, info, strlen (info));
    Http_print (fd, http400);
    close (fd);
    exit (0);
    break;
  case 1:
    break;
  default:
    info = "server bug\n";
    write (1, info, strlen (info));
    Http_print (fd, http400);
    close (fd);
    exit (0);
    break;
  }
  return c;
}

// separated by a space?
void getToken (int fd, int sepBySpace)
{  
  i = 0;
  char s[1024];//如果传过来的数据太大回把getToken的参数 int fd也覆盖掉，这样程序就会终止。
                //根据gdb调试得出缓冲区s地址为0xbffff9fc
  switch (ahead){
  case A_NONE:
    c = getChar (fd);
    break;
  case A_SPACE:
    ahead = A_NONE;
    Token_new(token, TOKEN_SPACE, 0);
    return;
  case A_CRLF:
    ahead = A_NONE;
    Token_new(token, TOKEN_CRLF, 0);
    return;
  default:{
    char *info = "server bug";
    write (1, info, strlen (info));
    Http_print (fd, http400);
    close (fd);
    exit (0);
    return;
  }
  }

  while (1){
    switch (c){
    case ' ':
      if (sepBySpace){
	if (i){
	  char *p;
	  int kind;
	  
	  // remember the ' '
	  ahead = A_SPACE;
	  s[i] = '\0';
	  p = malloc (strlen(s)+1);
	  strcpy (p, s);
	  kind = Token_getKeyWord (p);
	  if (kind>=0){
	    
	    Token_new (token, kind, 0);
	    return;
	  }
	  Token_new (token, TOKEN_STR, p);
	  return;
	}
	Token_new(token, TOKEN_SPACE, 0);
	return;
      }
      s[i++] = c;
      break;
    case '\r':{
      char c2;
      
      c2 = getChar (fd);
      if (c2=='\n'){
	if (i){
	  char *p;
	  int kind;
	  // remember the ' '
	  ahead = A_CRLF;
	  s[i] = '\0';
	  p = malloc (strlen(s)+1);
	  strcpy (p, s);
	  kind = Token_getKeyWord (p);
	  if (kind>=0){
	    Token_new (token, kind, 0);
	    return;
	  }
	  Token_new (token, TOKEN_STR, p);
	  return;
	}
	Token_new(token, TOKEN_CRLF, 0);
	return;
      }
      s[i++] = c;
      s[i++] = c2;
      break;
    }
    default:
      s[i++] = c;
      break;
    }
    c = getChar (fd);
  }
  return;
}

void parseError(int fd)
{
  //eatAllChars(fd);
  Http_print (fd, http400);
  close (fd);
  exit (0);
}

char *eatToken(enum TokenKind_t kind, int fd
	       , int sepBySpace)
{
  if (token.kind == kind){
    char *s = token.lexeme;
    advance (fd, sepBySpace);
    return s;
  }
  else {
    fprintf (stderr, "Error: parse error\n");
    fprintf (stderr, "expects: %s\n"
	     , TokenKind_toString (kind));
    fprintf (stderr, "but got: %s\n"
	     , TokenKind_toString(token.kind));
    parseError (fd);
  }
}

void advance(int fd, int sepBySpace)
{
  getToken(fd, sepBySpace);
}



ReqLine_t parseRequestLine (int fd)
{
  enum ReqKind_t kind;
  ReqLine_t reqline;
  
  switch(token.kind){
  case TOKEN_HEAD:
    kind = REQ_KIND_HEAD;
    break;
  case TOKEN_GET:
    kind = REQ_KIND_GET;
    break;
  default:
    parseError(fd);
    break;
  }
  advance(fd, 1);
      
  eatToken(TOKEN_SPACE, fd, 1);
  char *uri = eatToken(TOKEN_STR, fd, 1);
  eatToken(TOKEN_SPACE, fd, 1);
  eatToken(TOKEN_HTTP_ONE_ONE, fd, 1);
  eatToken(TOKEN_CRLF, fd, 1);
  
  if (DEBUG){
    fprintf (stderr, "uri=%s\n", uri);
  }

  reqline = ReqLine_new (0
			 , uri
			 , HTTP_ONE_ONE);
  ReqLine_print (1, reqline);
  return reqline;
}

void parseHeaders (int fd)
{
  fprintf (stderr, "header starting\n");
  while (token.kind != TOKEN_CRLF){
    // this should not be string...,
    // a dirty hack
    eatToken(TOKEN_STR, fd, 1);
    eatToken(TOKEN_SPACE, fd, 0);
    eatToken(TOKEN_STR, fd, 1);
    eatToken(TOKEN_CRLF, fd, 1);
    fprintf (stderr, "eeee");
  }
  return;
}

void parseBody (int fd)
{
  return;
}



Http_t Parse_parse (int fd)
{
  http400 = generate400();
  getToken(fd, 1);

  ReqLine_t reqline;
  Http_t http = 0;

  reqline = parseRequestLine (fd);
  parseHeaders(fd);
  if (token.kind!=TOKEN_CRLF)
    parseError(fd);
  parseBody(fd);    
  http = Http_new (HTTP_KIND_REQUEST
		   , reqline
		   , 0
		   , 0
		   , 0);
  
  if (DEBUG)
    Http_print (1, http);
  return http;
}

////////////////////////////////////
// 400
Http_t generate400()
{
  enum HttpKind_t kind = HTTP_KIND_RESPONSE;
  RespLine_t respLine;
  Header_t header = 0;
  char *body;
  Http_t http = 0;

  respLine = 
    RespLine_new (HTTP_ONE_ONE
		  , RESP_400
		  , "bad request");
  body = "";
  http = Http_new (kind
		   , 0
		   , respLine
		   , header
		   , body);
  return http;
}

