FLAG=-Wall -Wpedantic -Werror -ansi

all:		libb.so

#riga1: flag per la compilazione di librerie dinamiche
#riga2: nome in uscita e nome in entrata
#riga3: indicazione del soname
libb.so:	b.o
			gcc -shared ${FLAG} -fPIC \
			-o libb.so b.o \
			-Wl,-soname,libb.so

b.o:		b.c
			gcc -fPIC ${FLAG} -c b.c

.PHONY:		clean

#il - serve ad ignorare il valore di ritorno della funzione
clean:
			-rm *so *.o

