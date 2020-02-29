
all: main.o
	gcc allthreads.o -o s-talk  -pthread

main.o : allthreads.c 
	gcc -c allthreads.c 

clean:	
	rm -f  *.o all

