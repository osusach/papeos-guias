
#include "nodo.h"

typedef struct LEnlazada
{
	nodo *ini;
	nodo *fin;
} lista;

lista *CrearLista();
void AgregarFin(lista *l, int val);
int EliminarIni(lista *l);
int LargoLista(lista *l);