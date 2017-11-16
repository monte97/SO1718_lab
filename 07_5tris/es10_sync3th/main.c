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


int toBeExecuted = 1;
pthread_cond_t cond1, cond2, cond3;
pthread_mutex_t	mutex;

void *th1(void* arg) {
	while(1) {
		DBGpthread_mutex_lock(&mutex, "");
		/*finchè non è il mio turno*/
		while (toBeExecuted != 1){
			DBGpthread_cond_wait(&cond1, &mutex, "");
		}
		printf("In esecuzione 1\n");
		fflush(stdout);
		sleep(1); /*eseguo qualcosa*/
		/*dopo avere eseguito segnalo al secondo thread*/
		toBeExecuted = 2;
		DBGpthread_cond_signal(&cond2, "");
		DBGpthread_mutex_unlock(&mutex, "");
	}
}

void *th2(void* arg) {
	while(1) {
		DBGpthread_mutex_lock(&mutex, "");
		/*finchè non è il mio turno*/
		while (toBeExecuted != 2){
			DBGpthread_cond_wait(&cond2, &mutex, "");
		}
		printf("In esecuzione 2\n");
		fflush(stdout);
		sleep(1); /*eseguo qualcosa*/
		/*dopo avere eseguito segnalo al secondo thread*/
		toBeExecuted = 3;
		DBGpthread_cond_signal(&cond3, "");
		DBGpthread_mutex_unlock(&mutex, "");
	}
}
	

void *th3(void* arg) {
	while(1) {
		DBGpthread_mutex_lock(&mutex, "");
		/*finchè non è il mio turno*/
		while (toBeExecuted != 3){
			DBGpthread_cond_wait(&cond3, &mutex, "");
		}
		printf("In esecuzione 3\n");
		fflush(stdout);
		sleep(1); /*eseguo qualcosa*/
		/*dopo avere eseguito segnalo al secondo thread*/
		toBeExecuted = 1;
		DBGpthread_cond_signal(&cond1, "");
		DBGpthread_mutex_unlock(&mutex, "");
	}
}

int main (void) {

	//int i;
	pthread_t th;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond1, NULL);
	pthread_cond_init(&cond2, NULL);
	pthread_cond_init(&cond3, NULL);
	
	pthread_create(&th, NULL, th1, NULL);
	pthread_create(&th, NULL, th2, NULL);
	pthread_create(&th, NULL, th3, NULL);
	
	pthread_exit(NULL);
}