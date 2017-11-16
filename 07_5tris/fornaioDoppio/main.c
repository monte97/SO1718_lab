/*in ogni momento devono esserci due persone al nacone, quando vado al bancone è perchè è il mio turno
 *
 *
 * while (non è il mio turno ){
 *		aspetto
 * }
 *
 *	vado al bancone (il numero delle persone aumenta)
 *	se non c'è il massimo numero di persone allora chiamo qualcuno
 *
 *	mi servo
 *	
 *	tocca al prossimo (aumento e me ne vado, segnalandolo)
 *
 *
 *
 * */

#include <pthread.h>
#include "DBGpthread.h"
#include "printerror.h"

#include <stdio.h>



#define MAX_PRESENTI 	2
#define NUM_CLIENTI		10

int				dispenser_value = 0;
pthread_mutex_t	dispenser_mutex;


int 			turno_value = 0;
pthread_mutex_t	turno_mutex;
pthread_cond_t	turno_cond;
int				turno_presenti = 0;
void *cliente(void *arg) {

	char Clabel[128]={'a'};
	int biglietto;
	//int id;

	//id=(intptr_t)arg;

	while(1) {
		/*prendo il biglietto*/
		DBGpthread_mutex_lock(&dispenser_mutex,Clabel);
			printf("preso il bisglietto %d\n", dispenser_value);
			fflush(stdout);
			biglietto=dispenser_value;
			dispenser_value++;
		DBGpthread_mutex_unlock(&dispenser_mutex,Clabel);

		/*ho preso il biglietto*/
		DBGpthread_mutex_lock(&turno_mutex, Clabel);
		while(biglietto != turno_value) {
			DBGpthread_cond_wait(&turno_cond, &turno_mutex, Clabel);
		}
		
		/*e' il mio turno, se sono da solo faccio partire un altro*/
		turno_presenti++; /*aumento il numero di persone presenti*/
		if (turno_presenti < MAX_PRESENTI) { /*c'e' posto */
				turno_value++; /*mi ero scordato di incrementare il turno!*/
				DBGpthread_cond_broadcast( &turno_cond, Clabel);
				/*quindi tutti devono controllare
				se tocca a loro
				*/
		}
		/*non mi serve piu' la mutex sul turno quindi non mi serve piu' tenerla
		 *la mollo per ridurre la minimo la sezione critica,
		 *in questo modo altri hano la possibilita' di inserirsi
		 * */
		DBGpthread_mutex_unlock(&turno_mutex, Clabel);
		
		printf("Si serve %d\n", biglietto);
		fflush(stdout);
		sleep(1); /*attesa per simulare il servirsi*/
		

		/*me ne devo andare e segnalarlo*/
		DBGpthread_mutex_lock(&turno_mutex, Clabel);
		if (turno_presenti == MAX_PRESENTI) { 
			/*ne devo mandare via uno*/
			turno_value++;
			DBGpthread_cond_broadcast( &turno_cond, Clabel);
		}
		turno_presenti--;
		DBGpthread_mutex_unlock(&turno_mutex, Clabel);


		printf("%d se ne va\n", biglietto);
		fflush(stdout);
		pthread_exit(NULL);
	}

}


int main(void){

	pthread_t	th;
	int			rc;
	intptr_t	i;
	
	pthread_mutex_init(&turno_mutex, NULL);
	pthread_mutex_init(&dispenser_mutex, NULL);
	pthread_cond_init(&turno_cond, NULL);

	for (i = 0; i < NUM_CLIENTI; i++) {
		rc = pthread_create(&th, NULL, cliente, (void*)i);
		if (rc) PrintERROR_andExit(errno, "Failed to create th");
	}

	pthread_exit(NULL);
} 
