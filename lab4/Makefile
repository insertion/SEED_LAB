all:
	gcc -g -o touchstone server.c
	gcc -g -o filesv ./sql-lite3/sqlite3.o -l pthread -l dl ./sql-lite3/dbutil.c filesv.c token.c parse.c http-tree.c handle.c
	gcc -g -o banksv ./sql-lite3/sqlite3.o -l pthread -l dl ./sql-lite3/dbutil.c banksv.c  token.c parse.c http-tree.c handle.c
	gcc -fno-stack-protector -z execstack -g -o httpd  httpd.c token.c parse.c http-tree.c 
	sudo ./chroot-setup.sh

debug:
	gcc -DDEBUG -g -o touchstone server.c
	gcc -DDEBUG -g -o filesv ./sql-lite3/sqlite3.o -l pthread -l dl ./sql-lite3/dbutil.c filesv.c token.c parse.c http-tree.c handle.c
	gcc -DDEBUG -g -o banksv ./sql-lite3/sqlite3.o -l pthread -l dl ./sql-lite3/dbutil.c banksv.c  token.c parse.c http-tree.c handle.c
	gcc -DDEBUG -fno-stack-protector -z execstack -g -o httpd  httpd.c token.c parse.c http-tree.c 
	sudo ./chroot-setup.sh
	cd /jail
	sudo ./touchstone

clean:
	rm -rf touchstone filesv banksv httpd 
