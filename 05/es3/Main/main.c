#include <stdio.h>
#include "a.h"
#include "b.h"

/*
 *Devo includere i file.h delle librerie, in fase di compilazione devo 
 specificare i percorsi
 * */

int main(int argc, char* argv[]) {

		printf("%f", calcolaA( calcolaB( (double) atoi ( argv[1]) ) ) );
		return 0;

}
