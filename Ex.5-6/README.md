# Part 1:
in the given hello.c file, the memory leak occures because there is a memory allocation at the begginning of each loop iteration, 
but this memory is never freed. 

# Part 2:
commands to run the DDD attached to valgrind:
from terminal 1:
```
make valgrind_gdb_server
```
from terminal 2:
```
make ddd
```
after that, in the DDD console window, type:
```
(gdb) target remote | vgdb
```

(optional:) after finishing the debugging, close DDD manually and type:
```
ps aux | grep valgrind
kill -9 <valgrind_pid_1>
kill -9 <valgrind_pid_2>
```
to close the valgrind process.
