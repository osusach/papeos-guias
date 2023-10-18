#ifndef NODO_H
#define NODO_H

typedef struct Nodo
{
	int val;
	struct Nodo *nxt;
} nodo;

nodo *CrearNodo();
void EliminarNodo(nodo *n);
#endif