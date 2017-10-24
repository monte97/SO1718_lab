#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "alloca.h"

int main(void){
	int32_t *p;
	int i;

	ALLOCA(p);
	for (i = 0; i < 10; i++){
		printf("%d\n",p[i]);
	}
	return 0;
}
