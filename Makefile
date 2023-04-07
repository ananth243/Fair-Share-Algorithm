a.out: driver.c queue.o freeMem.o
	gcc -o a.out driver.c queue.o freeMem.o

queue.o: queue.c fairShareSched.h
	gcc -c queue.c

freeMem.o: freeMem.c fairShareSched.h
	gcc -c freeMem.c

clean:
	rm *.o *.out