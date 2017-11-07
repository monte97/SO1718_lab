SHELL=/bin/bash
LIBADIR=../libA
LIBBDIR=../libB
FLAGS=-Werror -Wpedantic -Werror -ansi

all:		main.exe
		
			#dipende anche dalle librerie condivise! 
            #gcc -shared -fPIC ${FLAGS} SBAGLIATO! non sto generado 
			#una libreria dinamica ma un file eseguibile!
			#non devo specificare -shared -fPIC
            
            #-o main.exe main.c
			#sbagliato! non devo compilare con il .c ma con il .o 
			#generato a parte!
#specificare in quale directory si trovano le librerie se diversa da quella di sistema
#dipende anche dai .h delle librerie condivise!
#nome compatto della libreria
#x ogini libreria dinamica lui deve sapere:
	#nome compatto
	#percorso della directory
	#rpath
main.exe:	main.o $(LIBADIR)/liba.so ${LIBBDIR}/libb.so 
			gcc ${FLAGS} \
			-o main.exe main.o \
			-la	\
			-L${LIBADIR} \
			-Wl,-rpath,`pwd`/${LIBADIR} \
			-lb \
			-L${LIBBDIR} \
			-Wl,-rpath,`pwd`/${LIBBDIR}


#non serve -fPIC perchè non sto linkando librerie dinamiche
#-I è il persorso degli headerfile
main.o:		main.c ${LIBADIR}/a.h ${LIBBDIR}/b.h
			gcc -c ${FLAGS} -I${LIBADIR} -I${LIBBDIR}  main.c

.PHONY:		clean

#il - serve ad ignorare il valore di ritorno
clean:
			-rm -f *.exe *.o
		
		#x ogini libreria dinamica lui deve sapere:
			#nome compatto
			#percorso della directory
			#rpath
