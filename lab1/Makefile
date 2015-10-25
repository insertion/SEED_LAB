all:	server.c httpd.c parse.c token.c http-tree.c broswer.c
	@gcc -g -m32 -o touchstone -z execstack -fno-stack-protector server.c
	@gcc -g -m32 -o httpd -z execstack -fno-stack-protector httpd.c token.c parse.c http-tree.c handle.c
	@gcc -g -m32 -o broswer broswer.c
stack1: stack1.c
	@gcc -g -m32 stack1.c -o stack1

stack2: stack2.c
	@gcc -g -m32 -z execstack -fno-stack-protector stack2.c -o stack2

test-shell: test-shell.c
	@gcc -m32 -z execstack test-shell.c -o test-shell
broswer: broswer.c
	@gcc -m32 broswer.c -o broswer

clean:
	@rm -rf touchstone httpd stack1 stack2 test-shell broswer 
