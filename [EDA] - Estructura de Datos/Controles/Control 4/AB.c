#include <stdio.h>
#include <stdlib.h>

// Lucas Mesias

typedef struct NodoArbol
{
    int dato;
    struct NodoArbol *izq;
    struct NodoArbol *der;
}nodoA;

typedef struct Arbol
{
    nodoA *raiz;

} arbol;

nodoA *CrearNodoA(int i)
{
    nodoA *res = malloc(sizeof(nodoA));
    res->izq = NULL;
    res->der = NULL;
    res->dato = i;
    return res;
}

arbol *CrearArbol()
{
    arbol *res = malloc(sizeof(arbol));
    res->raiz = NULL;
    return res;
}

nodoA *BuscarNodoRecu(nodoA *n, int bus)
{
    if (n->dato == bus)
        return n;
    else
    {
        // buscar por la izquierda
        nodoA *aux = NULL;
        if (n->izq != NULL)
            aux = BuscarNodoRecu(n->izq, bus);
        if (aux != NULL && aux->dato == bus)
            return aux;
        else
        {
            // buscar por la derecha
            if (n->der != NULL)
                aux = BuscarNodoRecu(n->der, bus);
            if (aux != NULL && aux->dato == bus)
                return aux;
        }
        // si no se encuentra retorna NULL
        return aux;
    }
}

nodoA *BuscarNodo(arbol *t, int bus)
{
    return BuscarNodoRecu(t->raiz, bus);
}

void Insertar(arbol *t, int padre, int x)
{
    if (padre == -1)
    {
        t->raiz = CrearNodoA(x);
    }
    else
    {
        nodoA *nPadre = BuscarNodoRecu(t->raiz, padre);
        if (nPadre == NULL)
        {
            printf("Problema al insertar\n");
            return;
        }
        if (nPadre->izq == NULL)
            nPadre->izq = CrearNodoA(x);
        else
            nPadre->der = CrearNodoA(x);
    }
}

int EsHoja(nodoA *n)
{
    if (n->der == NULL && n->izq == NULL)
        return 1;
    return 0;
}

void Preorden(nodoA *n)
{
    if (n == NULL)
        return;

    printf(" %d", n->dato);
    Preorden(n->izq);
    Preorden(n->der);
}

void Inorden(nodoA *n)
{
    if (n == NULL)
        return;

    Inorden(n->izq);
    printf(" %d", n->dato);
    Inorden(n->der);
}

void Postorden(nodoA *n)
{
    if (n == NULL)
        return;
    
    Postorden(n->izq);
    Postorden(n->der);
    printf(" %d", n->dato);
}

// la función recursiva busca desde la raiz hasta el nodo objetivo
int ProfundidadNodoRecu(nodoA *n, int x)
{
    // casos base: objetivo encontrado y llegar hasta una hoja
    if (n->dato == x)
        return 1;

    if (EsHoja(n))
        return 0;

    if (n->izq != NULL)
    {
        int prof = ProfundidadNodoRecu(n->izq, x);
        if (prof > 0)
        {
            return prof + 1;
        }
    }
    if (n->der != NULL)
    {
        int prof = ProfundidadNodoRecu(n->der, x);
        if (prof > 0)
        {
            return prof + 1;
        }
    }
    return 0;
}

int ProfundidadNodo(arbol *t, int x)
{
    // al resultado se le resta 1 porque la raiz comienza desde nivel 0
    return ProfundidadNodoRecu(t->raiz, x) - 1;
}
