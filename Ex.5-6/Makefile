CC = gcc
CFLAGS = -Wall -g

all: valgrind

hello: hello.c
	$(CC) $(CFLAGS) $< -o $@

valgrind: hello
	@mkdir -p valgrindReport
	valgrind -s --leak-check=full --log-file=valgrindReport/valgrindReport.txt ./hello this is a test

valgrind_gdb_server: hello
	valgrind -s --leak-check=full --track-origins=yes --vgdb=yes --vgdb-error=0 ./hello this is a test

ddd: hello
	ddd ./hello --debugger gdb

gdb: hello
	gdb ./hello
	(gdb) target remote | vgdb

clean:
	rm -rf hello valgrindReport