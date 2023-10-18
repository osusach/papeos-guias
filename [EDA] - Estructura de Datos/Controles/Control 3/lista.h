typedef struct nodol
{
    int valor;
    int p;
    struct nodol *next;
} Nodol;

typedef struct Lista
{
    Nodol *inicio;
    int largo;
} lista;

Nodol *crear_nodo(int valor, int ponderado);
lista *crear_lista();
int isEmptyL(lista *l);
void insertar_final(lista *l, int valor, int ponderado);
int *valor_inicial(lista *l);
int *valor_pos(lista *l, int pos);
int eliminar_pos(lista *l, int pos);
int eliminar_inicio(lista *l);
void imprimir_lista(lista *l);