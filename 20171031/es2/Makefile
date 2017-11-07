LIBRARIES=-lcmph #come ha trovato questo nome?
LIBPATH=/home/monte/Documents/uni/SO/lab/20171031/es2/LIB/lib
INCLUDEPATH=/home/monte/Documents/uni/SO/lab/20171031/es2/LIB/include

all:					file_adapter_ex2.exe
	
file_adapter_ex2.exe:	file_adapter_ex2.o
						gcc  -o file_adapter_ex2.exe -Wl,-rpath,${LIBPATH} -L${LIBPATH} file_adapter_ex2.o ${LIBRARIES}

file_adapter_ex2.o:		file_adapter_ex2.c
						gcc -c file_adapter_ex2.c -I${INCLUDEPATH}

.PHONY:					clean

clean:
						rm -f *.exe *.o
