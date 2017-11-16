/* mutex.c */

#define _THREAD_SAFE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include "printerror.h"
#define NUMTHRDS 10

pthread_t callThd[NUMTHRDS];
pthread_mutex_t mutexdata;   
/* this variable can be initialized statically with default attributes, using
   pthread_mutex_t mutexdata = PTHREAD_MUTEX_INITIALIZER;  
   same as pthread_mutex_init(...,NULL)
   but with NO ERROR CHECKING 
*/

int data;

void *decrementa(void *arg)
{
	int rc;
	
	rc = pthread_mutex_lock (&mutexdata);
	if( rc ) PrintERROR_andExit(errno,"pthread_mutex_lock failed");
	if(data>0) {
		sleep(1); /* provare a decommentare */
		/*al posto di intptr_t aveva usato un int classico*/
		printf("sono threadi %" PRIdPTR " ho decrementato data \n", (intptr_t)arg );
		fflush(stdout);
		data--;
	}
	rc = pthread_mutex_unlock (&mutexdata); /* provare a commentare */
	if( rc ) PrintERROR_andExit(errno,"pthread_mutex_unlock failed");
	pthread_exit((void*) 0);
}

int main (int argc, char *argv[])
{
	intptr_t i;
	int rc; 

	data=NUMTHRDS/2;
	rc = pthread_mutex_init (&mutexdata, NULL);
	if( rc != 0 ) PrintERROR_andExit(errno,"pthread_mutex_init failed");
	for(i=0;i < NUMTHRDS;i++) 	{
		rc = pthread_create ( &callThd[i], NULL,decrementa, (void *)i );
		if( rc != 0 ) PrintERROR_andExit(errno,"pthread_create failed");
	}

	printf ("data = %d \n", data);

	/*manca la join, come prima*/
	rc = pthread_mutex_destroy (&mutexdata);
	if( rc != 0 ) PrintERROR_andExit(errno,"pthread_mutex_destroy failed");

	return(0);
}

