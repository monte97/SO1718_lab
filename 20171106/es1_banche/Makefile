SHELL=/bin/bash
CFLAGS= -Wall -Wpedantic -Werror -std=gnu99
LIBS= -lpthread #libreria necessaria per la gestione dei pthread

all:		main.exe

#in fase di linking specifico le librerie che mi servono
main.exe:	main.o
			gcc ${CFLAGS} -o main.exe main.o  ${LIBS}
	
main.o:		main.c
			gcc -c ${FLAGS} main.c

.PHONY:		clean

clean:		
			-rm -f *.o main.exe
