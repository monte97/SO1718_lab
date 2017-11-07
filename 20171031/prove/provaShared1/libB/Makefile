FLAGS=-Wall -Wpedantic -Werror -ansi

all:		libb.so
	
libb.so:	b.o
			gcc -shared -fPIC ${FLAGS} \
			-o libb.so b.o \
			-Wl,-soname,libb.so

b.o:		b.h
			gcc -c ${FLAGS} -fPIC b.c

.PHONY:		clean

clean:
			-rm *.so *.o
