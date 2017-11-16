/*
ProduttoriA scrivono dati sul bufferA
ProduttoriB scrivono dati sul bufferB

ConsumatoriA+B hanno bisogno di un dato di entrambi i tipi

ESISTE UN SOLO BUFFER ANCHE SE È PER DUE TIPI DI DATO

a differenza di NProdMcons qui ho due tipi di consumatori che devono girare insieme
	

*/



#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>	/* uint64_t intptr_t */
#include <inttypes.h>	/* uint64_t  PRIiPTR */
#include <sys/time.h>	/* gettimeofday()    struct timeval */
#include <pthread.h> 

#include "printerror.h"
#include "DBGpthread.h"


#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif
#define 		STAMPA

#define 		CONSUM_NUM 10
/*int 			consum_wait = 0;
int 			consum_waitSignal = 0;*/
pthread_cond_t	consum_cond;

#define 		BUFFER_NUM_AB 1


pthread_mutex_t	mutex;

int				bufferA_pieni = 0;
int 			bufferA_value = 0;
pthread_cond_t	bufferA_cond;
int 			bufferA_prodWait = 0;

#define			PROD_A 3;

int				bufferB_pieni = 0;
int 			bufferB_value = 0;
pthread_cond_t  bufferB_cond;
int 			bufferB_prodWait = 0;

#define			PROD_B 5;



void* produttoreA(void *arg) {
	int 		prodotto = 0;
	intptr_t  	id = (intptr_t )arg;
	char 		Plabel[180];

	sprintf(Plabel, "A %" PRIdPTR"",id);
	while(1) {
		
		sleep(1);
		printf("ProduttoreA %" PRIdPTR " ha prodotto\n", id);
		fflush(stdout);
		prodotto++; /*ho prodotto qualcosa fuori dalla sezione critica*/

		/*ho finito di produrre quindi mi metto in attesa del buffer*/
		DBGpthread_mutex_lock(&mutex, Plabel);
		/*controlla se ha deve mettersi in attesa
		si deve mettere in attesa se
			in attesa ci sono abbastanza produttori per rimepire il buffer
		*/
		if (bufferA_prodWait >= (BUFFER_NUM_AB - bufferA_pieni)) {
			bufferA_prodWait++; /*un nuovo produttore si mette in attesa*/
			printf("ProduttoreA %" PRIdPTR " si mette in attesa\n", id);
			fflush(stdout);
			DBGpthread_cond_wait(&bufferA_cond, &mutex, Plabel);
			printf("ProduttoreA %" PRIdPTR " si sveglia\n", id);
			fflush(stdout);
			/*se sono qui sono stato svegliato*/
			/*SEMBRA INUTILE FARE UN -- SUBITO DOPO MA 
			* VISTA LA WAIT NEL MENTRE POTREBBE ESSERE ACCADUTO QUALCOSA! 
			*/
			bufferA_prodWait--;
			
		}

		/*qualcuno mi ha svegliato quindi devo produrre
		dal momento che mi hanno svegliato ho la lock
		*/
		bufferA_value = prodotto;
		bufferA_pieni++;

		/*ho finito di produrre quidni devo svegliare un consumatore
		posso segliarlo direttamente senza controlli perchè sarà il consumatore
		a verificare di potere consumare
		*/
		printf("ProduttoreA %" PRIdPTR " ha messo qualcosa nel buffer quindi sveglia un cliente\n", id);
		fflush(stdout);

		DBGpthread_cond_signal(&consum_cond, Plabel);

		

		DBGpthread_mutex_unlock(&mutex, Plabel);
	}
}

/*comportamento analogo all'altro produttore ma scambia buffer_a con buffer_b*/
void* produttoreB(void *arg) {
	int 		prodotto = 0;
	intptr_t  	id = (intptr_t )arg;
	char 		Plabel[180];

	sprintf(Plabel, "A %" PRIdPTR"",id);
	while(1) {
		
		sleep(1);
		printf("ProduttoreB %" PRIdPTR " ha prodotto\n", id);
		fflush(stdout);
		prodotto++; /*ho prodotto qualcosa fuori dalla sezione critica*/

		/*ho finito di produrre quindi mi metto in attesa del buffer*/
		DBGpthread_mutex_lock(&mutex, Plabel);
		/*controlla se ha deve mettersi in attesa
		si deve mettere in attesa se
			in attesa ci sono abbastanza produttori per rimepire il buffer
		*/
		if (bufferB_prodWait >= (BUFFER_NUM_AB - bufferB_pieni)) {
			bufferB_prodWait++; /*un nuovo produttore si mette in attesa*/
			printf("ProduttoreB %" PRIdPTR " si mette in attesa\n", id);
			fflush(stdout);
			DBGpthread_cond_wait(&bufferB_cond, &mutex, Plabel);
			printf("ProduttoreB %" PRIdPTR " si sveglia\n", id);
			fflush(stdout);
			/*se sono qui sono stato svegliato*/
			/*SEMBRA INUTILE FARE UN -- SUBITO DOPO MA 
			* VISTA LA WAIT NEL MENTRE POTREBBE ESSERE ACCADUTO QUALCOSA! 
			*/
			bufferB_prodWait--;
		
		}

		/*qualcuno mi ha svegliato quindi devo produrre
		dal momento che mi hanno svegliato ho la lock
		*/
		bufferB_value = prodotto;
		bufferB_pieni++;

		/*ho finito di produrre quidni devo svegliare un consumatore
		posso segliarlo direttamente senza controlli perchè sarà il consumatore
		a verificare di potere consumare
		*/
		printf("ProduttoreB %" PRIdPTR " ha inserito nel buffer quindi sveglia un consumatore\n", id);
		fflush(stdout);
		DBGpthread_cond_signal(&consum_cond, Plabel);
		

		DBGpthread_mutex_unlock(&mutex, Plabel);
	}
}


void *consumatore(void* arg) {
	char 		Clabel[180];
	intptr_t 	id;
	//int 		val = 0;

	id = (intptr_t )arg;
	sprintf(Clabel, "C %" PRIdPTR "", id);

	while (1) {
		/*inizio prendendo la lock*/
		DBGpthread_mutex_lock(&mutex, Clabel);

		/*prima di mettermi a consumare vedo se ho le risorse per farlo*
		devo aspettare finchè entrambi sono vuoti
		*/

		while ( (bufferA_pieni == 0) || (bufferB_pieni == 0)){
			DBGpthread_cond_wait(&consum_cond,&mutex, Clabel);
		}
		

		/*passato il ciclo posso consumare
		se consumo allora devo ridurre di uno il nu
		*/
		//val = bufferA_value + bufferB_value;
		printf("Consumatore %" PRIdPTR " consuma e sveglia un produttore per tipo\n", id);
		fflush(stdout);
		bufferA_pieni--;
		bufferB_pieni--;
		/*finito di consumare sengalo ai produttori
		per ogni tipo di thread segnalo e incremento il numero dei thread segnalati
		*/
	
		DBGpthread_cond_signal(&bufferA_cond, Clabel);
		DBGpthread_cond_signal(&bufferB_cond, Clabel);
		

		/*alla fine mollo la risorsa condivisa*/
		DBGpthread_mutex_unlock(&mutex, Clabel);

		sleep(1); 
	}

}

int main (int argc, char* argv[] )  {
	pthread_t    th; 
	int  		 rc;
	intptr_t 	 i;


	rc = pthread_cond_init(&bufferA_cond, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&bufferB_cond, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init(&consum_cond, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_mutex_init(&mutex, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");



	for(i=0; i < CONSUM_NUM; i++) {
		pthread_create( &th,NULL, consumatore,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	for(i=0; i < 5; i++) {
		rc=pthread_create( &th,NULL, produttoreA, (void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	for(i=0; i < 3; i++) {
		rc=pthread_create( &th,NULL, produttoreB, (void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL); 

	return(0); 
} 
