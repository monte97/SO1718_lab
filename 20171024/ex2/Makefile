CFLAG = -Wall -Wpedantic -Werror
INCLUDEDIR = ./INCLUDE
all:		main.exe

main.exe:	main.o
		gcc ${CFLAG} -o main.exe main.o

main.o:		main.c
		gcc -c -I${INCLUDEDIR} ${CFLAG} main.c

clean:
		-rm main.exe *.o

#per compilare senza linkare (generazione dei .o) devo usare anche il flag -c
#quando compilo il .c devo inserire -I per indicare dove trovare i file .h che usa
