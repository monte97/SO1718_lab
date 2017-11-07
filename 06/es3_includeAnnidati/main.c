#include "struttura.h"
#include "avvicina.h"
#include "distanza.h"
#include <stdio.h>
int main(void){
	Punto A = {1,3};
	Punto B = {2,2};
	avvicinaAllOrigine(&B);
	printf("%f\n", distanza(A,B));
}
