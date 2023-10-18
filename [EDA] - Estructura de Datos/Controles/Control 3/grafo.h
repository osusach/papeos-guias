typedef struct Grafo grafo;

struct Grafo
{
    int e;
    int v;
    lista **M;
};

grafo *crear_grafo(int n);
void insertar_arista(grafo *g, int ar1, int ar2, int p);
void mostrar_grafo(grafo *g);
void remover_arista(grafo *g, int ar1, int ar2);
int existe_arista(grafo *g, int ar1, int ar2);
int **obtener_aristas(grafo *g);
int obtener_grado_vertice(grafo *g, int vertice);
lista *obtener_adyacentes_vertice(grafo *g, int vertice);
;
int *grado_vertices(grafo *g);