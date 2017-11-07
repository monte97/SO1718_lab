SHELL=/bin/bash
FLAGS=-Wall -Wpedantic -Werror -ansi
LIBA=../libA
LIBB=../libB

all:	main.exe

#x ogni libreria dinamica vogliamo:
	#-l con il nome compatto
	#-L con percorso
	#-Wl,-rpath con il persorso
main.exe:	main.o	${LIBA}/liba.so ${LIBB}/libb.so
			gcc ${FLAGS} \
			-o main.exe main.o\
			-la \
			-L ${LIBA} \
			-Wl,-rpath,`pwd`/${LIBA} \
			-lb \
			-L ${LIBB} \
			-Wl,-rpath,`pwd`/${LIBB}

main.o:		main.c ${LIBA}/a.h ${LIBB}/b.h
			gcc -c ${FLAGS} -I${LIBA} -I${LIBB} main.c

.PHONY:		clean

clean:
			-rm *.exe *.o
