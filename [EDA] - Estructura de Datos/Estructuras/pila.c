#include <stdlib.h>
#include "nodo.h"

typedef struct Pila
{
	nodo *ini;
	nodo *fin;
} pila;

pila *CrearPila()
{
	pila *c = malloc(sizeof(pila));
	c->ini = NULL;
	return c;
}

void Apilar(pila *c, int val)
{
	nodo *n = CrearNodo();
	n->val = val;
	n->nxt = c->ini;
	c->ini = n;
}

int Desapilar(pila *c)
{
	nodo *aux = c->ini;
	c->ini = aux->nxt;
	return aux->val;
}

// retorna 1 si esta vacia
int PilaVacia(pila *c)
{
	if (c->ini == NULL)
		return 1;
	else
		return 0;
}