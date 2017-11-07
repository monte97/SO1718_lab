SHELL=/bin/bash
FLAGS=-Wall -Wpedantic -Werror -ansi
all:		liba.so

#-shared == sto compilando una lib dinamica
#-fPIC == position indipendent compilation

#ogni libreria dinamica ha bisogno di:
	#opzioni dedicata al gcc
	#soname per indicare il nome della libreria dinamica
liba.so:	a.o #NON dipende dal .h ma dal .o! prima devo compilare il c!
			gcc -shared ${FLAGS} -fPIC \
			-o liba.so a.o \
			-Wl,-soname,liba.so

a.o:		a.h
			gcc -c ${FLAGS} -fPIC a.c


.PHONY:		clean

#il - serve a
clean:	
			-rm *.o *.so
