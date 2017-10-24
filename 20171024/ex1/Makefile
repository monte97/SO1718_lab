CFLAG = -ansi -Wall -pedantic -Werror
LIB = -lm
INCLUDE = ./INCLUDE

all:		main.exe

main.exe:	main.o dimezza.o quadrato.o
		gcc ${CFLAG} -o main.exe main.o dimezza.o quadrato.o ${LIB}

main.o:		main.c ${INCLUDE}/dimezza.h ${INCLUDE}/quadrato.h
		gcc -c ${CFLAG} -I${INCLUDE} -o main.o main.c

dimezza.o:	dimezza.c
		gcc -c ${CFLAG} dimezza.c

quadrato.o:	quadrato.c
		gcc -c ${CFLAG} quadrato.c

clean:
		-rm main.exe *.o

#nei .o delle funzioni non è presente il file .h come dipendenza perchè non viene incluso nel .c
#in main.exe è presente il -lm perchè ha bisogno per trovare il .c della libreria
#in dimezza.o non ne ho bisogno perchè sto semplicentemente aggiungendo il .h che riesce a trovare da solo
