#include <stdlib.h>

typedef struct Nodo
{
	int val;
	struct Nodo *nxt;
} nodo;

nodo *CrearNodo()
{
	nodo *n = malloc(sizeof(nodo));
	n->val = 0;
	n->nxt = NULL;
	return n;
}

void EliminarNodo(nodo *n)
{
	if (n != NULL)
		free(n);
}