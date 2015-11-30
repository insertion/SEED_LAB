#include<stdio.h>
#include<string.h>

#include"sqlite3.h"


#define DEBUG 1
#define ERROR -1
#define SUCCESS 0

sqlite3* db;//定义一个数据库对象

int handle_db(sqlite3 *db, const char* sql);

int open_db()
{
	int user_user = sqlite3_open("./db/users.db",&db);//bind user.db with db
        if(user_user){
	  fprintf(stderr, "open db failed!  %s\n", sqlite3_errmsg(db));
	  sqlite3_close(db);
	  return ERROR;
        }else{  
	  if(DEBUG)
	    printf("open db success!\n");
	  return SUCCESS;
	}
}


void init_db()
{	
  if(open_db()==SUCCESS){//first call opendb
    //if user table is not exists,this sql could be useful,or useless!!!so wo first drop table user
    char* sql = "CREATE TABLE IF NOT EXISTS user(\
			id INTEGER PRIMARY KEY,	 \
                    	name VARCHAR(50),	 \
                    	passwd VARCHAR(50),	 \
			address VARCHAR(50)      \
        	    )";//define a string whinch is used to handle db
    
    handle_db(db,sql);//handle
    sqlite3_close(db);//colse db
    
  }	
}

int use_db(const char* u_name, const char* u_passwd, int Login)
{
    
    int result = select_db(u_name, u_passwd, Login);//call select_db
    
    if(result)
      return 1;
    else
      return 0;    
}

int register_db(const char* u_name, const char* u_passwd)
{ 
  //  sqlite3_close(db);
  if(open_db()==SUCCESS){
    
    char sql[1024];
    sprintf(sql, "INSERT INTO user(name, passwd) VALUES ('%s', '%s')", u_name, u_passwd);
   
    handle_db(db, sql);
    sqlite3_close(db);
  }
  else{
    if(DEBUG)
      printf("open failed![%s]\n",sqlite3_errmsg(db));
  } 
}


int select_db(const char* u_name, const char* u_passwd, int Login)
{
  if(DEBUG)
    printf("[%s]  [%s]\n", u_name, u_passwd);
  
  if(open_db()==SUCCESS){
    
        char sql[1024];
	if(Login)
	  sprintf(sql, "SELECT * from user WHERE name = '%s' AND passwd= '%s' ", u_name, u_passwd);
	else
	  sprintf(sql, "SELECT * from user WHERE name = '%s'", u_name);
	int row,column;
	char **result;
	char *errorMsg; 
	sqlite3_get_table(db, sql, &result, &row, &column, &errorMsg);
	if(DEBUG)
	  printf("rows: [%d] \n",row);
	
       	handle_db(db,sql);
        sqlite3_close(db);
	return row;
  }else{
    if(DEBUG)
      printf("open failed![%s]\n",sqlite3_errmsg(db));
  }
}

int handle_db(sqlite3 *db, const char* sql)
{
  char* error;
  int num =sqlite3_exec(db, sql, 0, 0, &error);	//lib fucntion
  printf("hanle_db  %s\n",error);	
  if(error){
    printf("operate failed! [%s]\n", sql);
    return ERROR;
  }else{
    if(DEBUG)
      printf("operate success! \n");
    return num;
  }
}
	
/*
void main()
{
  
  int t = use_db("zat","123",1);
  if(t)
    printf("Login success*************\n");
  else
    printf("Login fail**************\n");

  t = use_db("sb","123",0);
  if(t)
    printf("user exist*****\n");
  else
    {
      printf("user no exist*************\n");
      register_db("sb", "123");
    }
}
*/
