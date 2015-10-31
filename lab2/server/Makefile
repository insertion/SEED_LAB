all:
	@gcc -m32 -g -o touchstone server.c
	@gcc -m32 -fno-stack-protector -z noexecstack -g -o httpd httpd.c token.c parse.c http-tree.c handle.c

exec5:  
	@gcc -m32 -g -o touchstone server.c
	@gcc -m32 -fno-stack-protector -z noexecstack -g -o httpd httpd.c token.c parse.c http-tree.c handle.c

chag:
	@gcc -m32 -g -o touchstone server.c
	@gcc -m32 -fstack-protector-all -z noexecstack -g -o httpd httpd.c token.c parse.c http-tree.c handle.c


clean:
	@rm -rf touchstone httpd
