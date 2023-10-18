#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"

grafo *crear_grafo(int n)
{
    grafo *g = malloc(sizeof(grafo *));
    g->e = 0;
    g->v = n;
    g->M = malloc(sizeof(lista **) * n);
    for (int i = 0; i < n; i++)
    {
        g->M[i] = crear_lista();
    }
    return g;
}

void insertar_arista(grafo *g, int ar1, int ar2, int p)
{
    if (existe_arista(g, ar1, ar2) == 0)
    {
        insertar_final(g->M[ar1], ar2, p);
        insertar_final(g->M[ar2], ar1, p);
    }
    else
    {
        printf("arista ya agregada\n");
    }
}

void mostrar_grafo(grafo *g)
{
    printf("Grafo:\n");
    for (int i = 0; i < g->v; i++)
    {
        if (g->M[i]->largo != 0)
        {
            printf("%i: ", i);
            for (int j = 0; j < g->M[i]->largo; j++)
            {
                printf("%i ", valor_pos(g->M[i], j)[0]);
            }
            printf("\n");
        }
    }
}

void remover_arista(grafo *g, int ar1, int ar2)
{
    int indice1 = -1;
    int indice2 = -1;
    int *x, *y;
    if (g->M[ar1]->largo != 0)
    {
        for (int j = 0; j < g->M[ar1]->largo; j++)
        {
            x = valor_pos(g->M[ar1], j);
            if (x[0] == ar2)
            {
                indice1 = j;
            }
        }
        for (int i = 0; i < g->M[ar2]->largo; i++)
        {
            y = valor_pos(g->M[ar2], i);
            if (y[0] == ar1)
            {
                indice2 = i;
            }
        }
        if (indice1 != -1 && indice2 != -1)
        {
            printf("Arista (%i, %i), (%i, %i) eliminada\n", ar1, ar2, ar2, ar1);
            eliminar_pos(g->M[ar1], indice1);
            eliminar_pos(g->M[ar2], indice2);
            g->e -= 2;
        }
    }
}

int existe_arista(grafo *g, int ar1, int ar2)
{
    if (g->M[ar1]->largo != 0)
    {
        for (int j = 0; j < g->M[ar1]->largo; j++)
        {
            if (valor_pos(g->M[ar1], j)[0] == ar2)
            {
                return 1;
            }
        }
    }
    return 0;
}

int **obtener_aristas(grafo *g)
{
    int **aristas = malloc(sizeof(int **) * g->e / 2);
    int x = 0;
    int *aux;

    for (int i = 0; i < g->e / 2; i++)
    {
        aristas[i] = malloc(sizeof(int *) * 3);
        aristas[i][0] = -1;
        aristas[i][1] = -1;
        aristas[i][2] = 0;
    }

    for (int i = 0; i < g->v; i++)
    {
        if (g->M[i]->largo != 0)
        {
            for (int j = 0; j < g->M[i]->largo; j++)
            {
                aux = valor_pos(g->M[i], j);
                if (aux[0] > i)
                {
                    aristas[x][0] = i;
                    aristas[x][1] = aux[0];
                    aristas[x][2] = aux[1];
                    ++x;
                }
            }
        }
    }
    return aristas;
}

int obtener_grado_vertice(grafo *g, int vertice)
{
    int grado = 0;
    if (g->M[vertice]->largo != 0)
    {
        for (int j = 0; j < g->M[vertice]->largo; j++)
        {
            grado += 1;
        }
    }
    return grado;
}

lista *obtener_adyacentes_vertice(grafo *g, int vertice)
{
    lista *l = crear_lista();
    int *aux;
    if (g->M[vertice]->largo != 0)
    {
        for (int j = 0; j < g->M[vertice]->largo; j++)
        {
            aux = valor_pos(g->M[vertice], j);
            insertar_final(l, aux[0], aux[1]);
        }
    }
    return l;
}

int *grado_vertices(grafo *g)
{
    int *grd_vertices = malloc(sizeof(int *) * g->v);

    for (int i = 0; i < g->v; ++i)
    {
        grd_vertices[i] = obtener_grado_vertice(g, i);
    }

    return grd_vertices;
}

// int *grados_extremos(grafo *g){
//     int *grados_extr = malloc(sizeof(int*) * 2);
//     int aux1, aux2, *grad_vertices;

//     grad_vertices = grado_vertices(g);
//     aux1 = grad_vertices[0], aux2 = grad_vertices[0];
//     for(int i = 1; i < g -> v; ++i){
//         if(aux1 > grad_vertices[i]){
//             aux1 = grad_vertices[i];
//         }
//         if(aux2 < grad_vertices[i]){
//             aux2 = grad_vertices[i];
//         }
//     }
//     grados_extr[0] = aux1, grados_extr[1] = aux2;

//     return grados_extr;
// }

// int grafo_simple(grafo *g){
//     int contador;
//     lista *adj;
//     for(int i = 0; i < g -> v; ++i){
//         adj = obtener_adyacentes_vertice(g, i);
//         for(int j = 0; j < adj -> largo; ++j){
//             contador = 0;
//             for(int k = 0; k < adj -> largo; ++k){
//                 if(valor_pos(adj, j) == valor_pos(adj, k)){
//                     ++contador;
//                 }
//             }
//             if(contador > 1){
//                 printf("%i \n", contador);
//                 return 0;
//             }
//         }
//     }
//     return 1;
// }

// int clique(grafo *g, int *vertices, int largo){
//     if(largo > 2 && largo < g -> v){
//         for (int i = 0; i < largo; ++i){
//             for(int j = 1; j < largo; ++j){
//                 if(existe_arista(g, vertices[i], vertices[j]) == 0 && j != i){
//                     return 0;
//                 }
//             }
//         }
//         if(existe_arista(g, vertices[0], vertices[largo - 1]) == 1){
//             return 1;
//         }
//         else{
//             return 0;
//         }
//     }
//     else{
//         return 0;
//     }
// }

// int tour(grafo *g, int *vertices, int largo){
//     if(largo < g -> v){
//         for(int i = 0; i < largo - 1; ++i){
//                 if(existe_arista(g, vertices[i], vertices[i + 1]) == 0){
//                     return 0;
//                 }
//             }
//         return 1;
//     }
//     return 0;
// }

// void complemento(grafo *g){
//     FILE *fp = fopen("Complemento.txt", "w");
//     fprintf(fp, "%i\n", g -> v);
//     for(int i = 0; i < g -> v; ++i){
//         for(int j = 0; j < g -> v; ++j){
//             if(existe_arista(g, i, j) == 0 && i < j){
//                 fprintf(fp, "%i %i\n", i, j);
//             }
//         }
//     }
//     printf("Archivo grafo complemento creado\n");
// }

// void imprimir_aristas(grafo *g, int **aristas){
//     printf("Aristas: ");
//     for(int j = 0; j < g -> e; j++){
//         printf("(%i, %i) ", aristas[j][0], aristas[j][1]);
//     }
//     printf("\n");
// }

// void imprimir_vertices(lista *l, int ar1){
//      printf("Vertices Adyacentes a %i: ", ar1);
//     for(int j = 0; j < l -> largo; j++){
//         printf("%i ", valor_pos(l, j)[0]);
//     }
//     printf("\n");
// }