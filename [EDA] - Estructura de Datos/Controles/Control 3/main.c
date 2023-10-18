#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"

/*
IMPORTANTE:

1.- Si el grafo contiene n vertices, el programa
creara vertices desde el 0 hasta el n-1 por tanto se trabajara con el
0 como el vertice 1 y el n-1 como el vertice n

2.- Dado que el TDA grafo esta previamente creado de forma
que cuando se agrega una arista en el contador se le suma 2 dado
que si se agrega por ej (0, 1) tambien se agrega (1, 0) al ser no
dirigido tomando al par como 2 aristas y no 1 entonces la catidad
m de aristas sera multiplicada por 2 para poder trabajar sin problemas
con las funciones previamente creadas

3.- La forma de entregar parametros por consola es la siguiente:
ejecutable.exe x nombre opción
donde x es el numero de parametros el cual sera siempre 4
nombre el nombre del archivo con la extension .txt
opción 1 o 2 para indicar si quiere ejecutar el problema 1
de las estadisticas o el problema 2 del arbol de cobertura

4.- Para utilizar debe cambiar los nombres de los TDA a solo lista y
grafo para que no mande error de que no existen los datos
*/

// funcion que abre el archivo y verifica si fue abierto corretamente
FILE *abrir_archivo(char *nombre_archivo, char *modo)
{
    FILE *arch = fopen(nombre_archivo, modo);

    // se verifica si se abre
    if (arch == NULL)
    {
        printf("Nombre incorrecto o el archivo no existe\n");
        return NULL;
    }

    printf("Archivo abierto correctamente\n");
    return arch;
}

// funcion que toma como entrada un archivo con el grafo y entrega el
// grafo leido
grafo *leer_archivo(FILE *fp)
{
    int n, m;
    int v1, v2, p;

    fscanf(fp, "%i %i", &n, &m);

    grafo *g = crear_grafo(n);
    g->e = m * 2;

    for (int i = 0; i < m; ++i)
    {
        fscanf(fp, "%i %i %i", &v1, &v2, &p);
        insertar_arista(g, v1 - 1, v2 - 1, p);
    }

    fclose(fp);

    return g;
}

// funcion que cuenta los mayores al promedio
int costes_mayores(grafo *g, int prom)
{
    int count = 0;

    for (int i = 0; i < g->v; ++i)
    {
        for (int j = 0; j < g->M[i]->largo; ++j)
        {
            if (valor_pos(g->M[i], j)[1] > prom)
            {
                count += 1;
            }
        }
    }

    return count / 2;
}

// funcion para ordenar los ponderados
void ordenar_ponderados(int **aristas, grafo *g)
{
    int *aux;

    for (int i = 0; i < g->e / 2; ++i)
    {
        for (int j = 0; j < g->e / 2; ++j)
        {
            ;
            if (aristas[i][2] < aristas[j][2])
            {
                aux = aristas[i];
                aristas[i] = aristas[j];
                aristas[j] = aux;
            }
        }
    }
}

// funcion para copiar grafo
grafo *copiar_grafo(grafo *g)
{
    grafo *g_copia = crear_grafo(g->v);
    g_copia->e = g->e;
    int **aristas = obtener_aristas(g);

    for (int i = 0; i < g->e / 2; ++i)
    {
        insertar_arista(g_copia, aristas[i][0], aristas[i][1], aristas[i][2]);
    }

    return g_copia;
}

// Problema 1: Estadisticas del grafo

void estadisticas_grafo(grafo *g)
{
    float densidad = (float)g->e / (g->v * (g->v - 1));
    float grado_prom;
    float coste_prom;
    float auxi = 0;
    int mayores;

    // donde se obtiene el coste promedio
    for (int i = 0; i < g->v; ++i)
    {
        for (int j = 0; j < g->M[i]->largo; ++j)
        {
            auxi += valor_pos(g->M[i], j)[1];
        }
    }
    coste_prom = auxi / g->e;

    // mayores al coste promedio
    mayores = costes_mayores(g, coste_prom);

    // donde se obtiene el grado promedio
    auxi = 0;
    for (int i = 0; i < g->v; ++i)
    {
        auxi += obtener_grado_vertice(g, i);
    }
    grado_prom = auxi / g->v;

    printf("número de aristas que superan el peso promedio: %i aristas sobre el peso promedio (%.2f)\n", mayores, coste_prom);
    printf("grados promedio de los nodos: %.2f\n", grado_prom);
    printf("densidad: %.2f\n", densidad);
}

// Problema 2: Arbol de cobertura minimo

void MST(grafo *g)
{
    int **aristas = obtener_aristas(g);
    FILE *fp = abrir_archivo("grafo_MST.txt", "w");
    int *vertices = malloc(sizeof(int *) * g->v);
    int visitado, pertenece1, pertenece2;
    int index = 0;
    int count = 0;
    grafo *g_aux = crear_grafo(g->v);

    for (int i = 0; i < g->v; ++i)
    {
        vertices[i] = -1;
    }

    ordenar_ponderados(aristas, g);

    fprintf(fp, "%i %i\n", g->v, g->v - 1);

    for (int i = 0; i < g->e / 2; ++i)
    {
        visitado = 0;
        for (int j = 0; j < g->v; ++j)
        {
            if (vertices[j] == aristas[i][0] || vertices[j] == aristas[i][1])
            {
                visitado += 1;
            }
        }
        if (visitado < 2)
        {
            fprintf(fp, "%i %i %i\n", aristas[i][0] + 1, aristas[i][1] + 1, aristas[i][2]);
            insertar_arista(g_aux, aristas[i][0], aristas[i][1], aristas[i][2]);
            count += aristas[i][2];

            pertenece1 = 0;
            pertenece2 = 0;
            for (int j = 0; j < g->v; ++j)
            {
                if (vertices[j] == aristas[i][0])
                {
                    pertenece1 = 1;
                }
                if (vertices[j] == aristas[i][1])
                {
                    pertenece2 = 1;
                }
            }
            if (pertenece1 == 0)
            {
                vertices[index] = aristas[i][0];
                ++index;
            }
            if (pertenece2 == 0)
            {
                vertices[index] = aristas[i][1];
                ++index;
            }
        }
    }

    fprintf(fp, "%i", count);
}

void MST2(grafo *g)
{
    int *vertices = malloc(sizeof(int *) * g->v);
    for (int i = 0; i < g->v; ++i)
    {
        vertices[i] = -1;
    }
    vertices[0] = 0;

    lista *lista[g->v];
    int index = 1;
    int min;

    for(int i = 0; g->v; ++i)
    {
        for(int j = 0; j < index; ++j)
        {
            lista[j] = obtener_adyacentes_vertice(g, vertices[i]);
        }
        for(int j = 0; j < index; ++j)
        {
            for(int j = 0; j < index; ++j)
            {
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp = abrir_archivo(argv[2], "r");
    grafo *g = leer_archivo(fp);

    int op = atoi(argv[3]);

    if (op == 1)
    {
        printf("Estadisticas del grafo:\n");
        estadisticas_grafo(g);
    }
    else if (op == 2)
    {
        MST(g);
        printf("Arbol recubridor minimo creado\n");
    }
    return 0;
}