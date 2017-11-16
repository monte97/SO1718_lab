SHELL=/bin/bash
CFLAGS=-std=gnu99 -Wall -Wpedantic -Werror
LIBS=-lpthread

all:					CondVarSignal.exe

CondVarSignal.exe:		CondVarSignal.o
						gcc ${CLFAGS} -o CondVarSignal.exe CondVarSignal.o ${LIBS}

CondVarSignal.o:		CondVarSignal.c printerror.h
						gcc -c ${CFLAGS} CondVarSignal.c

.PHONY:		clean

clean:
			-rm *.exe *.o
