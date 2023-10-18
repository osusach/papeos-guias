#include <stdlib.h>
#include <stdio.h>
#include "nodo.h"

typedef struct Lista
{
	nodo *ini;
	nodo *fin;
} lista;


lista *CrearLista()
{
	lista *l = malloc(sizeof(lista));
	l->ini = NULL;
	l->fin = NULL;
	return l;
}

void AgregarFin(lista *l, int val)
{
	nodo *n = CrearNodo();
	n->val = val;
	n->nxt = NULL;
	if (l->ini == NULL)
	{
		l->ini = n;
		l->fin = n;
	}
	else
	{
		l->fin->nxt = n;
		l->fin = n;
	}
}

int EliminarIni(lista *l)
{
	nodo *aux = l->ini;
	l->ini = aux->nxt;
	return aux->val;
}

int LargoLista(lista *l)
{
	nodo *aux = l->ini;
	int res = 0;
	while (aux != NULL)
	{
		res++;
		aux = aux->nxt;
	}
	return res;
}