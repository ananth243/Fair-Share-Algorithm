a.out: driver.c queue.o freeMem.o job.o set.o
	gcc -o a.out driver.c queue.o freeMem.o job.o set.o

job.o:	job.c fairShareSched.h
	gcc -c job.c
queue.o: queue.c fairShareSched.h
	gcc -c queue.c

set.o: set.c fairShareSched.h
	gcc -c set.c
freeMem.o: freeMem.c fairShareSched.h
	gcc -c freeMem.c

clean:
	rm *.o *.out