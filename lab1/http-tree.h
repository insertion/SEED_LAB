#ifndef HTTP_TREE_H
#define HTTP_TREE_H

/////////////////////////////////////////
// http version
enum HttpVersion_t{
  HTTP_ONE_ZERO,
  HTTP_ONE_ONE,
  HTTP_TWO_ZERO,
};



///////////////////////////////////////
// request line
enum ReqKind_t{
  REQ_KIND_GET,
  REQ_KIND_HEAD,
};

typedef struct ReqLine_t *ReqLine_t;
struct ReqLine_t
{
  enum ReqKind_t kind;
  char *uri;
  enum HttpVersion_t httpversion;
};

ReqLine_t ReqLine_new (enum ReqKind_t kind
		       , char *uri
		       , enum HttpVersion_t v);

/////////////////////////////////////
// response line
enum RespKind_t{
  RESP_200,
  // client error
  RESP_400,
  RESP_404,
};

typedef struct RespLine_t *RespLine_t;
struct RespLine_t
{
  enum HttpVersion_t httpversion;
  enum RespKind_t kind;
  char *info;
};

RespLine_t RespLine_new (enum HttpVersion_t v
			 , enum RespKind_t kind
			 , char *info);

/////////////////////////////////////
// headers
typedef struct Header_t *Header_t;
struct Header_t
{
  int junk;
};



////////////////////////////////////
// http
enum HttpKind_t{
  HTTP_KIND_REQUEST,
  HTTP_KIND_RESPONSE,
};
 
typedef struct Http_t *Http_t;
struct Http_t
{
  enum HttpKind_t kind;
  ReqLine_t reqLine;
  RespLine_t respLine;
  Header_t headers;
  char *body;
};

Http_t Http_new (enum HttpKind_t kind
		 , ReqLine_t reqLine
		 , RespLine_t respLine
		 , Header_t headers
		 , char *body);
void Http_print (int fd, Http_t http);

#endif
