pretest: pretest.c
	@gcc -o pretest pretest.c -g -fno-stack-protector
stack2:
	@gcc -m32 -z noexecstack -g -o stack2 stack2.c

exec3:
	@gcc -m32 -fno-stack-protector -z noexecstack -g -o exec3 exec3.c

clean:
	@rm -rf stack2 exec3 pretest core
