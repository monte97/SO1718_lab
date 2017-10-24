#define ALLOCA(PTR)					\
do{							\
	PTR = (int32_t*) calloc(10, sizeof(int32_t));	\
	if (PTR != NULL) {				\
		int i;					\
		for (i = 0; i < 10; i++){		\
			PTR[i] = (-1000+i);		\
		}					\
	}						\
}while(0)
