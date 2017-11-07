FLAGS=-Wall -Wpedantic -Werror -ansi

all:		liba.so

#riga1: flag per segnalare che vogliamo una libreria dinamica, -fpic indica generare codice position indipendent
#riga2: nome del file di output e di input
#riga3: indicazione del soname che vogliamo per la libreria
liba.so:	a.o
			gcc -shared ${CFALG} -fPIC \
			-o liba.so a.o \
			-lm \
			-Wl,-soname,liba.so

#dato che questo modulo oggetto farà parte di una shared lib occorre compilarlo con -fPIC per ottenere codice poition indipendet
a.o:		a.c
			gcc -fPIC ${FLAGLS} -c a.c

.PHONY:		clean

#il - serve a dire di ignorare il valore di ritorno della funzione
clean:
			-rm -f *.o *.so
