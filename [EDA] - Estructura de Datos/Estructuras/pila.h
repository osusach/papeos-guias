#include "nodo.h"
typedef struct Pila
{
	nodo *ini;
	nodo *fin;
} pila;

pila *CrearPila();
void Apilar(pila *c, int val);
int Desapilar(pila *c);
int PilaVacia(pila *c);