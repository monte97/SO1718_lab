SHELL=/bin/bash
CFLAGS=-std=gnu99 -Wall -Wpedantic -Werror
LIBS=-lm

all:		main.exe
	
main.exe:	main.o avvicina.o distanza.o
			gcc ${CFLAGS} -o main.exe main.o avvicina.o distanza.o ${LIBS}

main.o:		main.c avvicina.h distanza.h 
			gcc -c ${CFLAGS} main.c

avvicina.o:	avvicina.c avvicina.h
			gcc -c ${CFLAGS} avvicina.c 

distanza.o:	distanza.c	distanza.h
			gcc -c ${CFLAGS} distanza.c ${LIBS}

.PHONY:		clean

clean:		
			-rm *.exe *.o
