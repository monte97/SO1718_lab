#include <stdlib.h>
#include <stdio.h>
#include "a.h"
#include "b.h"

int main(int argc, char* argv[]) {
	printf("%d\n", func_a(func_b(atoi(argv[1]))));
	return 0;
}
