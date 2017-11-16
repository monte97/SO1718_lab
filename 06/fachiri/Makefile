SHELL=/bin/bash
CFLAGS=-std=gnu99 -Werror -Wpedantic -Wall 
LIBS=-lpthread

all:			main.exe

main.exe:		main.
				gcc ${FLAGS} -o main.exe main.o ${LIBS}

main.o:			main.c
				gcc -c ${FLAGS} main.c

.PHONY:			clean

clean:			
				-rm *.out *.exe *.o
				
