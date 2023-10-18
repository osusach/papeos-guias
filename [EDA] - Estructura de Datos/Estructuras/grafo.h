
#include "pila.h"
typedef struct Grafo
{
	int n;
	int m;
	int **matriz;
} grafo;

grafo *CrearGrafo(int n);
void InsertarArista(grafo *g, int vert1, int vert2);
void MostrarGrafo(grafo *g);
void RemoverArista(grafo *g, int vert1, int vert2);
int PerteneceArista(grafo *g, int vert1, int vert2);
int ObtenerGradoVertice(grafo *g, int v);
pila *ObtenerAdyacentes(grafo *g, int vert);