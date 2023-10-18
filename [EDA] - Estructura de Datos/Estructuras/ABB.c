#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct NodoArbol
{
    char dato;
    struct NodoArbol *izq;
    struct NodoArbol *der;
}nodoA;

typedef struct Arbol
{
    nodoA *raiz;

} arbol;

nodoA *CrearNodoA(char c)
{
    nodoA *res = malloc(sizeof(nodoA));
    res->izq = NULL;
    res->der = NULL;
    res->dato = c;
    return res;
}

arbol *CrearArbol()
{
    arbol *res = malloc(sizeof(arbol));
    res->raiz = NULL;
    return res;
}

nodoA *BuscarNodoRecu(nodoA *n, char bus)
{
    if (n->dato == bus)
        return n;
    else
    {
        nodoA *aux = NULL;
        if (n->izq != NULL)
            aux = BuscarNodoRecu(n->izq, bus);
        if (aux != NULL && aux->dato == bus)
            return aux;
        else
        {
            if (n->der != NULL)
                aux = BuscarNodoRecu(n->der, bus);
            if (aux != NULL && aux->dato == bus)
                return aux;
        }
        return aux;
    }
}

nodoA *BuscarNodo(arbol *t, char bus)
{
    return BuscarNodoRecu(t->raiz, bus);
}

// solo cuando ya hay raiz
void Insertar(arbol *t, char padre, char x)
{
    nodoA *nPadre = BuscarNodo(t, padre);
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

    printf("%c ", n->dato);
    Preorden(n->izq);
    Preorden(n->der);
}

void Inorden(nodoA *n)
{
    if (n == NULL)
        return;

    Inorden(n->izq);
    printf("%c ", n->dato);
    Inorden(n->der);
}

void Postorden(nodoA *n)
{
    if (n == NULL)
        return;
    
    Postorden(n->izq);
    Postorden(n->der);
    printf("%c ", n->dato);
}

nodoA *BuscarPadre(nodoA *n, char bus)
{
    // la raiz no tiene padre
    if (n->dato == bus)
        return NULL;
    if (n->izq != NULL && n->izq->dato == bus)
        return n;
    if (n->der != NULL && n->der->dato == bus)
        return n;

    nodoA *aux = NULL;
    if (n->izq != NULL)
        aux = BuscarPadre(n->izq, bus);
    if (aux != NULL && aux->dato == bus)
        return aux;

    if (n->der != NULL)
        aux = BuscarPadre(n->der, bus);
    if (aux != NULL && aux->dato == bus)
        return aux;
    
    return aux;
}

int ProfundidadNodoRecu(nodoA *n, char x)
{
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

int ProfundidadNodo(arbol *t, char x)
{
    return ProfundidadNodoRecu(t->raiz, x) - 1;
}

int NivelNodo(arbol *t, char x)
{
    return ProfundidadNodo(t, x);
}

int AlturaNodoRecu(nodoA *n)
{
    if (EsHoja(n))
        return 1;

    int izq, der;

    if (n->izq != NULL)
    {
        izq = AlturaNodoRecu(n->izq);
        if (n->der == NULL)
            return izq + 1;
    }
    if (n->der != NULL)
    {
        der = AlturaNodoRecu(n->der);
        if (n->izq == NULL)
            return der + 1;
    }
    if (izq > der)
        return izq + 1;
    else
        return der + 1;
}

int AlturaNodo(arbol *t, char x)
{
    nodoA *n = BuscarNodo(t, x);
    return AlturaNodoRecu(n) - 1;
}

int ContarNodosRecu(nodoA *n)
{
    if (n == NULL)
        return 0;
    if (EsHoja(n))
        return 1;
    return ContarNodosRecu(n->izq) + ContarNodosRecu(n->der) + 1;
}

int ContarNodos(arbol *t)
{
    return ContarNodosRecu(t->raiz);
}

int ContarHojasRecu(nodoA *n)
{
    if (n == NULL)
        return 0;
    if (EsHoja(n))
        return 1;
    return ContarHojasRecu(n->izq) + ContarHojasRecu(n->der);
}

int ContarHojas(arbol *t)
{
    return ContarHojasRecu(t->raiz);
}

int SonSimilaresRecu(nodoA *n1, nodoA *n2)
{
    if ((n1->izq != NULL) != (n2->izq != NULL))
        return 1;
    if ((n1->der != NULL) != (n2->der != NULL))
        return 1;
    if ((n1->izq != NULL) && (n2->izq != NULL))
        if (SonSimilaresRecu(n1->izq, n2->izq))
            return 1;

    if ((n1->der != NULL) && (n2->der != NULL))
        if (SonSimilaresRecu(n1->der, n2->der))
            return 1;
    return 0;

}

int SonSimilares(arbol *t1, arbol *t2)
{
    if (SonSimilaresRecu(t1->raiz, t2->raiz))
        return 0;
    return 1;
}

nodoA *BuscarHoja(nodoA *n)
{
    if (n == NULL)
        return n;
    if (EsHoja(n))
        return n;
    return BuscarHoja(n->izq);
}

int EsCompleto(arbol *t)
{
    // buscar cualquier hoja, en este caso la de más a la izquierda
    nodoA *hoja = BuscarHoja(t->raiz);
    int prof = ProfundidadNodo(t, hoja->dato);
    int hojas = ContarHojas(t);
    // para que sea completo, todas las hojas deben ser del mismo nivel
    // por lo que siempre se cumple que cantidad de hojas = 2^nivel
    if (hojas == (int)pow(2, prof))
        return 1;
    return 0;
}
