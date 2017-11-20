CFLAGS=-ansi -Wpedantic -Wall -Werror -D_REENTRANT -D_THREAD_SAFE 
LIBS=-lpthread


all: 	 				barbiereAttento.exe

barbiereAttento.exe:  	main.o DBGpthread.o 
						gcc ${CFLAGS} -o barbiereAttento.exe main.o DBGpthread.o ${LIBS}

main.o: 				main.c DBGpthread.h printerror.h
						gcc -c ${CFLAGS} main.c 

DBGpthread.o: 			DBGpthread.c printerror.h
						gcc ${CFLAG} -c DBGpthread.c  


.PHONY:					clean

clean:
						-rm -f *.exe *.o


