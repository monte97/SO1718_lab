#ifndef THREAD_SAFE
	#define THREAD_SAFE
#endif

#ifndef POSIX_C_SOURCE
	#define POSIX_C_SOURCE	201112L
#endif

#define NUMFAC 2 
#define NUMSPA 10

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h> /*mi serve per usare gli intptr_t*/

pthread_mutex_t spade[NUMSPA];

void* usaSpada(void* arg) {
	int i;
	int rc;
	intptr_t fac = (intptr_t)arg;
	while (1) { /*finche' crash non ci separi*/
		for(i = 0; i < NUMSPA; i++) { /*per ogni spada, iniziando dalla prima*/
			rc = pthread_mutex_lock(&spade[i]); /*prendo la risorsa*/
			if (rc) exit(1);
				/*nella sezione critica stampo chi sono e cosa sto facendo*/
				printf("Fachiro %" PRIdPTR "usa %d \n", fac, i);
				fflush(stdout);
			rc = pthread_mutex_unlock(&spade[i]); /*rilascio la risorsa condivisa*/
			if (rc) exit(1);
		}
	}
}


int main(void) {
	int i;
	int rc;
	pthread_t th; /*questo a cosa cacchio serve?*/
	intptr_t arg; /*intero della dimensione di un puntatore generico, puo' essere usato per
	passare argomenti ad una funzione che prende void* evitando di allocare memoria*/
	for (i = 0; i < NUMSPA; i++) { /*inizializzo i lock*/
		rc = pthread_mutex_init(&spade[i], NULL);
		if (rc) exit(1);
	}

	/*faccio partire i thread, per ognuno alloco una variabile*/
	for (i = 0; i < NUMFAC; i++) {
		arg = i;
		rc = pthread_create(&th , NULL, usaSpada, (void*)arg); /*passaggio di un intero con le dimensioni di un puntatore, deve essere castato a puntatore generico*/
		if (rc) exit(1);
	}

	pthread_exit(NULL);	
}
