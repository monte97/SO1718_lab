/* file:  CondVarSignal.c 
   Routine che fornisce un synchronization point. 
   E' chiamata da ognuno dei SYNC_MAX pthread, che si fermano 
   finche' tutti gli altri sono arrivati allo stesso punto di esecuzione. 
*/ 

#define _THREAD_SAFE

#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h> 
#include "printerror.h"

#define SYNC_MAX 5

pthread_mutex_t  sync_lock; 
pthread_cond_t   sync_cond; 
int  sync_count = 0; 
int nextExit = 0; /*il primo ad uscire deve essere il primo ad entrare*/
void SyncPoint(void) 
{ 
	int rc;
	int turno;
	/* blocca l'accesso al counter */ 
	rc = pthread_mutex_lock(&sync_lock); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_lock failed"); /* no EINTR */
  
	/* incrementa il counter di quelli arrivati*/ 
	turno = sync_count++; 

	/* controlla se deve aspettare o no */ 
	if (sync_count < SYNC_MAX) {
		
		/*prima aspetta sempre finchè non si finisce*/
		rc = pthread_cond_wait(&sync_cond, &sync_lock); 
		if( rc ) PrintERROR_andExit(rc, "pthread_cond_wait failed"); /* no EINTR */

		/*continua ad aspettare finchè non è il suo turno di uscire*/
		while (turno != nextExit){
			/*se non è il mio turno ne sveglio uno e mi rimetto a dormire*/
			rc = pthread_cond_signal (&sync_cond); 
			if( rc ) PrintERROR_andExit(rc,"pthread_cond_signal failed"); /* no EINTR */
			
			rc = pthread_cond_wait(&sync_cond, &sync_lock); 
			if( rc ) PrintERROR_andExit(rc, "pthread_cond_wait failed"); /* no EINTR */
		} 
		
		/*sono uscito quindi passo al prssimo*/
		nextExit++;
		/*ne sveglio uno passando al prossimo*/
		rc = pthread_cond_signal (&sync_cond); /* senza questa signal ne terminano solo 2 */
		if( rc ) PrintERROR_andExit(rc,"pthread_cond_signal failed"); /* no EINTR */
	}
	else    {
		/* tutti hanno raggiunto il punto di barriera */ 
		rc = pthread_cond_signal (&sync_cond); 
		if( rc ) PrintERROR_andExit(rc,"pthread_cond_signal failed"); /* no EINTR */


		/*l'ultimo aspetta qui
			inserire anche qui un controllo per uscita
		*/
		rc = pthread_cond_wait(&sync_cond, &sync_lock); 
		if( rc ) PrintERROR_andExit(rc, "pthread_cond_wait failed"); /* no EINTR */

		while (turno != nextExit){
			/*se non è il mio turno ne sveglio uno e mi rimetto a dormire*/
			rc = pthread_cond_signal (&sync_cond); 
			if( rc ) PrintERROR_andExit(rc,"pthread_cond_signal failed"); /* no EINTR */
			
			rc = pthread_cond_wait(&sync_cond, &sync_lock); 
			if( rc ) PrintERROR_andExit(rc, "pthread_cond_wait failed"); /* no EINTR */
		} 
	}

	/* sblocca il mutex */ 
	rc = pthread_mutex_unlock (&sync_lock);  /* senza unlock ne termina solo 1 */ 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_unlock failed"); /* no EINTR */
	return; 
} 

void *Thread (void *arg) 
{ 
	pthread_t  th; 

	th=pthread_self();    /* thread identifier */ 
	printf ("%lu\n", th); 
	SyncPoint(); 
	printf("Sono %lu e sono uscito \n", th); 
	pthread_exit(NULL); 
} 

int main () 
{ 
	pthread_t    th[SYNC_MAX]; 
	int  rc; intptr_t i;
	void *ptr; 

	rc = pthread_cond_init(&sync_cond, NULL);
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_init failed"); /* no EINTR */
	rc = pthread_mutex_init(&sync_lock, NULL); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_init failed"); /* no EINTR */

	for(i=0;i<SYNC_MAX;i++) {
		rc = pthread_create(&(th[i]), NULL, Thread, NULL); 
		if (rc) PrintERROR_andExit(rc,"pthread_create failed"); /* no EINTR */
	}
	for(i=0;i<SYNC_MAX;i++) {
		rc = pthread_join(th[i], &ptr ); 
		if (rc) PrintERROR_andExit(rc,"pthread_join failed"); /* no EINTR */
	}

	rc = pthread_mutex_destroy(&sync_lock); 
	if( rc ) PrintERROR_andExit(rc,"pthread_mutex_destroy failed"); /*no EINTR*/
	rc = pthread_cond_destroy(&sync_cond); 
	if( rc ) PrintERROR_andExit(rc,"pthread_cond_destroy failed"); /*no EINTR*/
	pthread_exit (NULL); 
} 
  
  
  
