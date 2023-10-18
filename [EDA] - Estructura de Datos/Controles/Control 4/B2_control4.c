#include <stdio.h>
#include <stdlib.h>
#include "AB.h"

/*
USO: 
Compilar: "gcc B2_control4.c AB.c -o control.exe"
Ejecutar: "control.exe 2 <archivo>.txt"
*/

/*
El arbol entregado en el archivo de entrada debe ser binario, 
de lo contrario, se sobreescribirá el hijo derecho del nodo
que se sobrecargue con más de 2 hijos.
*/

FILE *abrir_archivo(char *nom)
{
	FILE *fp = fopen(nom, "r");
	if( fp == NULL)
	{
		printf("Problema con el archivo\n");
		return NULL;
	}
	else
	{
		printf("Archivo leido\n\n");
		return fp;
	}
}

arbol *LeerArbol(FILE *fp)
{
    int i = 0, k;
    arbol *ar = CrearArbol();
    while (fscanf(fp, "%d", &k) != EOF)
    {
        Insertar(ar, k, i);
        i++;
    }
    return ar;
}

void ProfundidadNodos(arbol *ar, int nNodos)
{
    // imprimir la profundidad de cada nodo
    for (int i = 0; i < nNodos; i++)
    {
        printf("Profundidad del nodo %d: %d\n", i, ProfundidadNodo(ar, i));
    }
}

void RecorridoEnPreorden(arbol *ar)
{
    printf("Recorrido en inorden: ");
    Preorden(ar->raiz);
    printf("\n");
}

void RecorridoEnInorden(arbol *ar)
{
    printf("Recorrido en inorden: ");
    Inorden(ar->raiz);
    printf("\n");
}

void RecorridoEnPostorden(arbol *ar)
{
    printf("Recorrido en inorden: ");
    Postorden(ar->raiz);
    printf("\n");
}

void NodosPorNivel(arbol *ar, int nNodos)
{
    printf("Nodos por nivel:\n");
    int *niveles = malloc(sizeof(int) * nNodos);
    int nivMax = 0;
    // obtener todos los niveles de cada nodo + el nivel máximo
    for (int i = 0; i < nNodos; i++)
    {
        // Profundidad de un nodo es lo mismo que su Nivel
        niveles[i] = ProfundidadNodo(ar, i);
        if (niveles[i] > nivMax)
            nivMax = niveles[i];
    }
    // imprimir cada nivel por categoria
    for (int i = 0; i <= nivMax; i++)
    {
        printf("Nivel %d:", i);
        for (int j = 0; j <= nNodos; j++)
        {
            if (niveles[j] == i)
                printf(" %d", j);
        }
        printf("\n");
    }

}

int main(int argc, char *argv[])
{
    FILE *fp = abrir_archivo(argv[2]);
    if (fp == NULL)
        return 1;

    int nNodos;
    fscanf(fp, "%d", &nNodos);

    arbol *ar = LeerArbol(fp);

    ProfundidadNodos(ar, nNodos);
    
    printf("\n");
    printf("\n");

    RecorridoEnPreorden(ar);
    RecorridoEnInorden(ar);
    RecorridoEnPostorden(ar);

    printf("\n");
    NodosPorNivel(ar, nNodos);

    fclose(fp);
}
