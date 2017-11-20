#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif0
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#else
#if _POSIX_C_SOURCE < 200112L
	#undef  _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif
#endif


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 

#include "printerror.h"
#include "DBGpthread.h"


#define ATLETI_N 4

pthread_mutex_t mutex;
/*un array per in modo da avere una condizione per ogni atleta e svegliare quello specifico?*/
pthread_cond_t attesaTurno[ATLETI_N];
pthread_cond_t attesaRisposta[ATLETI_N];
/*quale atleta ha il testimone*/
int turno = 0;
/*quale è il prossimo che deve andare*/
int next = 1;

void* atleta(void *arg) {
	intptr_t indice = (intptr_t) arg;
	intptr_t prossimoIndice = (indice + 1) % ATLETI_N;

	while(1) {
		DBGpthread_mutex_lock(&mutex,""); 

		/*quando posso correre?
		posso correre se è il mio turno

		all'inizio parto e basta, nei casi successivi mi fermo alla prima wait
		*/
		if (turno == indice && next){
			printf("Sto correndo %" PRIdPTR "\n", indice);
			fflush(stdout);
			sleep(1);
			next = 0;
		}	else {
			/*devo usar eude condizioni? una per attesa turno e una per scabio di info*/
			/*mi metto in attesa DEL MIO TURNO*/
			DBGpthread_cond_wait(&attesaTurno[indice], &mutex, "");
		}

		/*sono qui perchè ho finito quindi devo passare il testimone o perchè l'ho ricevuto?*/
		/*posso sapere in che caso sono controllando il turno*/
		if (turno == indice) {
			/*ho corso quidni devo svegliare il prossimo*/
			/*svegliandolo in questo punto riprende da prima di questo blocco di codice*/
			DBGpthread_cond_signal(&attesaTurno[prossimoIndice], "");
			/*dopo avere fatto la signal mi metto in attesa di una risposta*/
			DBGpthread_cond_wait(&attesaRisposta[indice], &mutex, "");
			/*dopo avere ricevuto la risposta mollo la mutua*/
			DBGpthread_cond_signal(&attesaRisposta[prossimoIndice], "");
			/*ho finito, ricomincia il ciclo e mi metto in attesa che torni il mio turno*/
		} else {
			/*sono stato svegliato con la signal perchè non è il mio turno*/
			/*segnalo che ho preso a quello del turno*/
			DBGpthread_cond_signal(&attesaRisposta[turno], "");
			/*mi metto in attesa della conferma*/
			DBGpthread_cond_wait(&attesaRisposta[indice], &mutex, "");
			/*dopo avere ricevuto la conferma posso modificare il turno*/
			DBGpthread_cond_signal(&attesaRisposta[turno], "");
			next = 1; /*io ho finito di correre quindi è il turno del prosismo*/
			turno = (turno + 1) % ATLETI_N;
		}

		DBGpthread_mutex_unlock(&mutex, "");
		
	}
}

int main(void) {
	intptr_t i;
	pthread_t th;

	/*inizializzare le varie cose usate*/

	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < ATLETI_N; i++) {
		if (pthread_cond_init(&attesaRisposta[i], NULL) ) return 1;;
		if (pthread_cond_init(&attesaTurno[i], NULL) ) return 2;
	}

	/*creo e avvio i vari thread, non devo fare altro*/
	for (i = 0; i < ATLETI_N; i++) {
		pthread_create(&th, NULL, atleta, (void *)i );
	}

	pthread_exit(NULL);
	return 0;
	
}
