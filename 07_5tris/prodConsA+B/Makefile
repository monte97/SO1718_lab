SHELL=/bin/bash
CFLAGS=-std=gnu99 -Wall -Wpedantic -Werror
LIBS=-lpthread

all:		main.exe

main.exe:		main.o DBGpthread.o
				gcc ${CFLAGS} -o main.exe main.o DBGpthread.o ${LIBS} #le lib dinahce sono aggiunte a runtime

main.o:		 	main.c DBGpthread.h printerror.h
				gcc -c ${CFLAGS} main.c
           
DBGpthread.o:	DBGpthread.h printerror.h DBGpthread.c
				gcc -c ${CFLAGS} DBGpthread.c

.PHONY:			clean

clean:			
				-rm -f *.exe *.o	