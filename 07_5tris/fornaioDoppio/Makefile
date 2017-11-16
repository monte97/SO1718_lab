SHELL=/bin/bash
CFLAGS=-std=gnu99 -Werror -Wall -Wpedantic
LIBS=-lpthread

all:			main.exe

main.exe:		main.o DBGpthread.o
				gcc ${CFLAGS} main.o DBGpthread.o -o main.exe ${LIBS}

main.o:			main.c
				gcc -c ${CFLAGS} main.c

DBGpthread.o:	DBGpthread.c printerror.h
				gcc -c ${CFLAGS} DBGpthread.c

.PHONY:			clean

clean:			
				-rm -f *.exe *.o
