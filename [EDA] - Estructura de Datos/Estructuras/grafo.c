#include <stdlib.h>
#include <stdio.h>
#include "pila.h"

typedef struct Grafo
{
	int n; // cant vertices
	int m; // cant matriz
	int **matriz;
} grafo;

// al crear el grafo, en la matriz se comienza a contar desde 0,
// por lo que se debe compensar para la correcta lectura de
// los vertices (n++), ya que en el problema se comienza desde 1
grafo *CrearGrafo(int n)
{
	n++;
	grafo *g = malloc(sizeof(grafo));
	g->n = n;
	g->m = 0;
	g->matriz = malloc(sizeof(int *)*n);
	for (int i = 0; i < n; i++)
	{
		g->matriz[i] = malloc(sizeof(int)*n);
		for (int j = 0; j < n; j++)
			g->matriz[i][j] = 0;
	}
	return g;
}

void InsertarArista(grafo *g, int vert1, int vert2)
{
	g->matriz[vert1][vert2] = 1;
	g->matriz[vert2][vert1] = 1;
	g->m += 1;
}

void MostrarGrafo(grafo *g)
{
	printf("Aristas del grafo:\n");
	for (int i=1; i < g->n; i++)
	{
		// j=i para imprimir solo las aristas en una direccion
		for (int j=i; j < g->n; j++)
		{
			if (g->matriz[i][j] == 1)
				printf("(%d, %d)", i, j);
		}
	}
	printf("\n");
}

void RemoverArista(grafo *g, int vert1, int vert2)
{
	g->matriz[vert1][vert2] = 0;
	g->matriz[vert2][vert1] = 0;
	g->m -= 1;
}

// revisar si hay una arista que contenga ambos vertices
int PerteneceArista(grafo *g, int vert1, int vert2)
{
	if (g->matriz[vert1][vert2] == 1)
		return 1;
	else
		return 0;
}


int ObtenerGradoVertice(grafo *g, int v)
{
	int res = 0;
    for (int i = 1; i < g->n; i++)
	{
		if (g->matriz[v][i] == 1)
		{
			res++;
		}
	}
	return res;
}

pila *ObtenerAdyacentes(grafo *g, int vert)
{
	pila *res = CrearPila();
	for (int i = 1; i < g->n; i++)
	{
		if (PerteneceArista(g, vert, i))
			Apilar(res, i);
	}
	return res;
}