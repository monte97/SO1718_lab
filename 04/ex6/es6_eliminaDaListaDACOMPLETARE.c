#include <stdio.h>
#include <stdlib.h>

typedef struct nodolista {    
	int key;
	struct nodolista *next;
} NODOLISTA;

void aggiungi_in_testa( int KEY, NODOLISTA* *proot) {
	NODOLISTA *ptr;
	ptr = (NODOLISTA*) malloc(sizeof(NODOLISTA));
	ptr->next = *proot;
	ptr->key = KEY;
	*proot = ptr;
}

void stampa(NODOLISTA *ptr) {
	printf("\n");
	while(ptr) {
		printf("%d ", ptr->key);
		ptr = ptr->next;
	}
	printf("\n");
}

/* FUNZIONE DA IMPLEMENTARE !!!!!! */
/*deve cercare nella lista il nodo con valore KEY ed eliminarlo, ritorna successo con 0, errore con 1*/
int  elimina( int KEY, NODOLISTA* *proot){
	NODOLISTA* *tmp;
	if ((*proot) == NULL){ /*non ho elementi*/
		return 1;
	}else {
		if ((*proot)->key == KEY) { /*caso in cui l'elemento da eliminare sia in testa*/
			tmp = proot;
			(*proot) = (*proot)->next;
			free(tmp);
			return 0;
		} else { /*se non è in testa allora cerco nel corpo*/
			/*finchè non ho finito la lista cerco nel successivo*/
			while ( ((*proot)->next != NULL) && ((*proot)->next->key != KEY) ){
				(*proot) = (*proot)->next;
			}
			/*quando sono qui se (*proot)->next è null allora non ho trovato occorrenze di KEY perchè sono arrivato alla */
			if ((*proot)->next == NULL) {
				return 1;
			} else {
				/*(*proot) è il nodo precendete alla */
				tmp = &((*proot)->next); /*nodo con la KEY*/
				(*proot)->next = (*tmp)->next; /*sflio dalla lista il nodo con la key collegando quello prima con quello dopo (rispetto a quello con la key)*/
				free(tmp); /*elimino il nodo con la keu*/
				return 0;
			}
		}
		
	}
}


int main() {
	NODOLISTA *root;
	root = NULL;

 	/* codice aggiunto per fare la prova */
	aggiungi_in_testa( 111, &root );
	aggiungi_in_testa( 111, &root );
	aggiungi_in_testa( 71,  &root );
	stampa(root);

	elimina( 4, &root);
	stampa(root);
	/*
	elimina( 111 , &root );
	stampa(root);
	elimina(  53 , &root );
	stampa(root);
	elimina(  71 , &root );
	stampa(root);
	elimina( 111 , &root );
	stampa(root);
	elimina(  10 , &root );
	stampa(root);*/

	return(0);
}

