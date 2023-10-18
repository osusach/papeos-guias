#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

lista *crear_lista()
{
    lista *l;
    l = (lista *)malloc(sizeof(lista));
    l->inicio = NULL;
    l->largo = 0;
    return l;
}

Nodol *crear_nodo(int valor, int ponderado)
{
    Nodol *n;
    n = (Nodol *)malloc(sizeof(Nodol));
    n->valor = valor;
    n->p = ponderado;
    n->next = NULL;
    return n;
}

int isEmptyL(lista *l)
{
    if (l->inicio == NULL)
    {
        return 1;
    }
    return 0;
}

void insertar_final(lista *l, int valor, int ponderado)
{
    Nodol *n;
    n = crear_nodo(valor, ponderado);
    if (isEmptyL(l) == 1)
    {
        l->inicio = n;
    }
    else
    {
        Nodol *aux = l->inicio;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = n;
    }
    l->largo += 1;
}

int *valor_inicial(lista *l)
{
    int *inicial = malloc(sizeof(int *) * 2);
    inicial[0] = l->inicio->valor;
    inicial[1] = l->inicio->p;
    return inicial;
}

int *valor_pos(lista *l, int pos)
{
    int *posi = malloc(sizeof(int *) * 2);
    Nodol *aux;
    if (pos > l->largo)
    {
        posi[0] = -1;
        posi[1] = -1;
    }
    else if (pos == 0)
    {
        posi = valor_inicial(l);
    }
    else
    {
        aux = l->inicio;
        for (int i = 0; i < pos; i++)
        {
            aux = aux->next;
        }
        posi[0] = aux->valor;
        posi[1] = aux->p;
    }
    return posi;
}

int eliminar_inicio(lista *l)
{
    int inicio;
    if (isEmptyL(l) == 1)
    {
        printf("lista vacia");
        inicio = -1;
        return inicio;
    }
    else
    {
        Nodol *aux = l->inicio;
        l->inicio = aux->next;
        inicio = aux->valor;
        l->largo--;
        free(aux);
        return inicio;
    }
}

int eliminar_pos(lista *l, int pos)
{
    int posi;
    Nodol *aux1, *aux2;
    if (pos > l->largo || isEmptyL(l) == 1)
    {
        printf("Posicion no valida");
        posi = -1;
        return posi;
    }
    else if (pos == 0)
    {
        posi = eliminar_inicio(l);
    }
    else
    {
        aux1 = l->inicio;
        aux2 = l->inicio->next;
        for (int i = 1; i < pos; i++)
        {
            aux1 = aux1->next;
            aux2 = aux2->next;
        }
        aux1->next = aux2->next;
        posi = aux2->valor;
        free(aux2);
        l->largo--;
    }
    return posi;
}

void imprimir_lista(lista *l)
{
    for (int j = 0; j < l->largo; j++)
    {
        printf("%i ", valor_pos(l, j)[0]);
        printf("\n");
    }
}
