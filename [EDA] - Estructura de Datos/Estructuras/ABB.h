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

nodoA *CrearNodoA(char c);
arbol *CrearArbol();
nodoA *BuscarNodoRecu(nodoA *n, char bus);
nodoA *BuscarNodo(arbol *t, char bus);
void Insertar(arbol *t, char padre, char x);
int EsHoja(nodoA *n);
void Preorden(nodoA *n);
void Inorden(nodoA *n);
void Postorden(nodoA *n);
nodoA *BuscarPadre(nodoA *n, char bus);
int ProfundidadNodoRecu(nodoA *n, char x);
int ProfundidadNodo(arbol *t, char x);
int NivelNodo(arbol *t, char x);
int AlturaNodoRecu(nodoA *n);
int AlturaNodo(arbol *t, char x);
int ContarNodosRecu(nodoA *n);
int ContarNodos(arbol *t);
int ContarHojasRecu(nodoA *n);
int ContarHojas(arbol *t);
int SonSimilaresRecu(nodoA *n1, nodoA *n2);
int SonSimilares(arbol *t1, arbol *t2);
nodoA *BuscarHoja(nodoA *n);
int EsCompleto(arbol *t);
