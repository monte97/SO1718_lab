/*compilare con -pthread perche' altrimenti dice che 
 *non trova una reference a pthread_create
 *indaga sul motivo!
 * */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE /*indico che voglio usare la versione safe delle funzioni*/
#endif

#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

#define NBANK 3
#define T_DEPO 5
#define T_PREL 4

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h> 
/*
 *Variabili globali
 Tj indica la quantità di denaro della banca J
 Nj incia il numero di operazioni effettuate dalla banca j
 * */

typedef struct{
	int B; /*denaro della banca*/
	int N; /*numero di operazioni svolte sulla banca*/
} Bank;

Bank banks[NBANK]; /*array di strutture ideonee a rappresentare una banca*/

pthread_mutex_t mutexdata; /**/

/*funzione da passare ad un thread,
 *deve predere in input un puntatore a generico
 * */
void *preleva(void* arg){
	/*Come accedere ai dati dell'argomenti:
	 *1)	castare il puntatore a void al tipo che mi serve
	 *2) 	risolvere l'indirizzo dell'argomento castato per accedere al dato
	 * */
	int index = *((int*)arg); 
	while(1){ /*ogni thread deve rappresentare un loop*/
		sleep(1); /*aspetta per un secondo*/
		/*inizio della sezione critica, devo garantire che un solo thread acceda alle risorsa*/
		pthread_mutex_lock(&mutexdata); /*effettuo il blocco sulla risorsa condivisa*/	
			printf("banca %d prelieva\n", index);
			fflush(stdout); /*forzo svuotaggio buffer per essere sicuro che il messaggio venga stampato asap*/		banks[index].B -= 9;/*accedo alla risorsa condivisa*/ 
			banks[index].N++;
			sleep(1);
		pthread_mutex_unlock(&mutexdata); /*rilascio la risorsa condivisa*/
	}
	pthread_exit(NULL);
}

void *deposita(void* arg){
	int index = *((int*) arg);
	while(1){
		sleep(1);
		pthread_mutex_lock(&mutexdata);
			printf("Banca %d deposita\n", index);
			fflush(stdout);
			banks[index].B += 10;
			banks[index].B++;
			sleep(1);
		pthread_mutex_unlock(&mutexdata);
	}
	pthread_exit(NULL);
}

/*thread della "banca dimu italia", periodicamente tenta di stampare lo stato delle banche*/
void *watch(void *arg){

	pthread_mutex_lock(&mutexdata);
		printf("Somma totale: %d", banks[1].B + banks[2].B + banks[3].B );
		printf("OP1: %d \tOP2: %d \tOP3: %d", banks[1].N, banks[2].N, banks[3].N);
	pthread_mutex_unlock(&mutexdata);
	sleep(30);

}

int main(void) {

	int i,k;
	int *p;
	pthread_t th;
	pthread_mutex_init(&mutexdata, NULL); /*inizializzo il lock sulla risorsa condivisa*/
	
	for (i = 0; i < NBANK; i++) {
		for (k = 0; k < T_DEPO; k++) {
			p = (int*) malloc(sizeof(int));
			*p = i;
			pthread_create(&th, NULL, deposita, p); 
		}
		for (k = 0; k < T_PREL; k++) {
			p = (int*) malloc(sizeof(int));
			*p = i;
			pthread_create(&th, NULL, preleva, p); 
		}
	}

	pthread_create(&th, NULL, watch, NULL);
	/*il MAIN viene eseguito sul suo thread, se si termina con la return 
	 *vengono uccisi anche i thread figli, con pthread_exit si esce dal solo thread corrente
	 * */
	pthread_exit(NULL); 	

}
