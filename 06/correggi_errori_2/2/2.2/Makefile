# Makefile per errore*
# a causa della presenza di strerror_r in printerror.h
# occorre compilare col flag -D_POSIX_C_SOURCE=200112L

CFLAGS=-ansi -Wpedantic -Wall -D_REENTRANT -D_POSIX_C_SOURCE=200112L
LIBRARIES=-lpthread

all: 	errore1_mutex.exe

errore1_mutex.exe: errore1_mutex.o
	gcc ${CFLAGS} -o errore1_mutex.exe errore1_mutex.o ${LIBRARIES}

errore1_mutex.o: errore1_mutex.c printerror.h
	gcc ${CFLAGS} -c errore1_mutex.c

.PHONY:	clean

clean:
	rm -f errore1_mutex.o errore1_mutex.exe

