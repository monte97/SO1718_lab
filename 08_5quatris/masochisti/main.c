/* file:  barbiere+saluto.c 
	  il barbiere, dopo avere finito il lavoro su un cliente,
	  lo saluta e lo manda via.
	  Il cliente non se ne va fino a che non e' stato salutato.
*/ 

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif


#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>	/* uint64_t */
#include <sys/time.h>	/* gettimeofday()    struct timeval */
#include <pthread.h> 
#include "printerror.h"
#include "DBGpthread.h"

#define LATI 2
#define A 4
#define B 3

typedef struct {
	int index; /* identificativo della macchine*/
	int type;  /* da quale lato arrivo? 0-1 */
} datiAuto;
/* variabili per la sincronizzazione */
int attesa[LATI] = {0}; /*numero di macchine in attesa per ogni lato*/
/*rappresenta l'intento di volere attraversare */
int vuoleAttraversare[LATI] = {0}; /*numero di auto che aspettano per attraversare il ponte, in teoria 0-1*/
pthread_mutex_t  ponte;
pthread_cond_t   condPonte[LATI]; 
pthread_cond_t   condAuto[LATI];

void* automobile(void* arg) {
	datiAuto car = *((datiAuto*)arg);
	char label[128];
	sprintf(label,"Auto%d",car.index);

	while(1) {
		DBGpthread_mutex_lock(&ponte, label);
		/*se dal mio lato non ho nessuno*/

		/*qualcuno è sulla wait nel lato opposto?*/
		if (vuoleAttraversare[(car.type + 1) % LATI]){
			/*in questo modo passa per primo il secondo che arriva*/
			printf("%d ATTRAVERSA lato %d\n", car.index, car.type );
			fflush(stdout);
			vuoleAttraversare[car.type] = 0; /*ho attraversato, nessuno (per adesso vuole attraversare dal mio lato*/
			//attesa[car.type]--; /*una macchina si è appena tolta dalle scatole*/
			car.type = (car.type + 1) % LATI; /*dopo avere attraversato devo andare dall'altro lato*/
			/*dopo avere attraversato dico all'altra macchina di potere andare*/
			DBGpthread_cond_signal(&condPonte[car.type], label); /*dato che ho già cambiato lato alla macchina posso fare così la signal sul lato opposto*/
		}else{
			/*nessuno del lato opposto vuole attraversare quindi aspetto*/
			vuoleAttraversare[car.type]++; /*da questo lato vogliono passare*/
			/*aspetto che un'altra auto arrivi dall'altro lato*/
			DBGpthread_cond_wait(&condPonte[car.type], &ponte, label);
			/*sono stato svegliato dall'altra auto, ora posso passare anche io*/
			printf("%d ATTRAVERSA lato %d\n", car.index, car.type );
			fflush(stdout);
			vuoleAttraversare[car.type]--;/*per adesso nessuono vuole passare da questo lato*/
			//attesa[car.type]--; /*una macchina si è appena tolta dalle scatole*/
			car.type = (car.type + 1) % LATI; /*dopo avere attraversato devo andare dall'altro lato*/
			/*a questo punto entrambe le macchine sono passate, segnalo entrambi i lati di avanzare*/
		}
		DBGpthread_mutex_unlock(&ponte, label);
		sleep(2);
	}
}

int main (int argc, char* argv[] ) { 
	pthread_t    th; 
	int  rc, i;
	datiAuto *car;
	int index = 0;

	rc = pthread_cond_init( &condPonte[0] , NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init( &condPonte[1] , NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init( &condAuto[0] , NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");
	rc = pthread_cond_init( &condAuto[1] , NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed");

	rc = pthread_mutex_init( &ponte, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed");

	for (i = 0; i < A; i++){
		car = (datiAuto *)malloc(sizeof(datiAuto));
		car->index = index++;
		car->type = 0;
		if (pthread_create(&th, NULL, automobile, (void*) car)) {
			return 1;
		}
	}

	for (i = 0; i < B; i++){
		car = (datiAuto *)malloc(sizeof(datiAuto));
		car->index = index++;
		car->type = 1;
		if (pthread_create(&th, NULL, automobile, (void*) car)) {
			return 1;
		}
	}
	pthread_exit(NULL); 
} 

  
  
