#include <math.h>
/*Non ha senso includere qui il .h, sto già definendo la funzione*/
static double salva;

double dimezza(double num) {
	salva = cos(num)/2.0; /*2.0 perchè voglio espiclitare una divisione tra numeri in virgola mobile*/
	return salva;
}
