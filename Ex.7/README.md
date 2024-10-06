# race condition analysis:
the problem with this code is that all the threads accesing the 'accum' variable without appropriate mutexing. 
this way, it is possible that two threads getting the same value of accum at the same time and each assign it to a value not based on the other's result. 
in summary, the value of accum becomming unpredictable. 

# helgrind analysis:
```
==9588== Possible data race during write of size 8 at 0x10C018 by thread #4
==9588== Locks held: none
==9588==    at 0x109215: square (raceCondition.c:13)
==9588==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==9588==    by 0x4909AC2: start_thread (pthread_create.c:442)
==9588==    by 0x499AA03: clone (clone.S:100)
==9588== 
==9588== This conflicts with a previous write of size 8 by thread #3
==9588== Locks held: none
==9588==    at 0x109215: square (raceCondition.c:13)
==9588==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
==9588==    by 0x4909AC2: start_thread (pthread_create.c:442)
==9588==    by 0x499AA03: clone (clone.S:100)
==9588==  Address 0x10c018 is 0 bytes inside data symbol "accum"
``` 
this report indicates that there might be a race condition between threads trying to write to the variable 'accum' as  explained above.