SHELL=/bin/bash
CFLAGS=-std=gnu99 -Wall -Wpedantic -Werror
LIBS=-lpthread

all:			main.exe

main.exe:		main.o DBGpthread.o
				gcc ${CFLAGS} -o main.exe main.o DBGpthread.o ${LIBS}

main.o:			main.c DBGpthread.h
				gcc -c ${CFLAGS} main.c DBGpthread.c

DBGpthread.o:	DBGpthread.h DBGpthread.c printerror.h
				gcc .c ${CFLAGS} DBGpthread.c

.PHONY:			clean

clean:
				*.exe *.o