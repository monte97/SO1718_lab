#include <stdio.h>
#include "dimezza.h"
#include "quadrato.h"
#define NUM 13.37

static double salva;

int main(void) {
	salva = dimezza(NUM);
	printf("%f", salva);
	salva = quadrato(salva);
	printf("%f", salva);
	return 0;
}
