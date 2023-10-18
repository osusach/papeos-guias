// Propiedad de Lucas Mesias 21266659-9

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

nodoA *CrearNodoA(int i);
arbol *CrearArbol();
nodoA *BuscarNodo(arbol *t, int bus);
nodoA *BuscarNodoRecu(nodoA *n, int bus);
void Insertar(arbol *t, int padre, int x);
int EsHoja(nodoA *n);
void Preorden(nodoA *n);
void Inorden(nodoA *n);
void Postorden(nodoA *n);
int ProfundidadNodo(arbol *t, int x);
int ProfundidadNodoRecu(nodoA *n, int x);
