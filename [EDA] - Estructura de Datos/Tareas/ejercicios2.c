#include <stdio.h>
#include <stdlib.h>

// variable generales para iterar
int i;
int j;

// Ejercicio 9.5

#define filas_3 3
#define columnas_4 4

void leer_filas(int *A)
{
    for(i = 0; i < (filas_3); i++)
    {
        for(j = 0; j < (columnas_4); j++)
        {
            printf("Ingrese el valor %d %d de la matriz: ", i + 1, j + 1);
            scanf("%d", A);
            A++;
        }        
    }
}

void imprimir_columnas(int A[filas_3][columnas_4])
{
    printf("La matriz es: \n");

    for(i = 0; i < columnas_4; i++)
    {
        printf("(");
        for(j = 0; j < filas_3; j++)
        {
            if( ((j+1) % filas_3) == 0)
            {
                printf("%d)\n", A[j][i]);
            }
            else
            {
                printf("%d ", A[j][i]);
            }
        }
    }
}

// Ejercicio 9.6

#define filas_m 4

void generar_matriz(int *A)
{
    for(i = 0; i < (filas_m); i++)
    {
        for(j = 0; j < (filas_m); j++)
        {
            printf("Ingrese el valor %d %d de la matriz: ", i + 1, j + 1);
            scanf("%d", A);
            A++;
        }        
    }
}

void imprimir_matriz(int A[filas_m][filas_m])
{
    printf("La matriz es: \n");

    for(i = 0; i < filas_m; i++)
    {
        printf("(");
        for(j = 0; j < filas_m; j++)
        {
            if( ((j+1) % filas_m) == 0)
            {
                printf("%d)\n", A[i][j]);
            }
            else
            {
                printf("%d ", A[i][j]);
            }
        }
    }
}

int suma_matriz(int A[filas_m][filas_m])
{
    int total_m = 0;

    for(i = 0; i < filas_m; i++)
    {
        for(j = 0; j < filas_m; j++)
        {
            if(j != i)
            {
                total_m += A[i][j];
            }
        }
    }

    return total_m;
}

// ejercicio 9.6 dinamico
int **crear_matriz_dinam(int n)
{
    int **A = (int **)malloc(sizeof(int *) * n);
    
    for(i = 0; i < n; i++)
    {
        A[i] = (int *)malloc(sizeof(int) * n);
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            printf("Ingrese el valor %d %d de la matriz: ", i + 1, j + 1);
            scanf("%d", &A[i][j]);
        }
    }

    return A;
}

void imprimir_matriz_dim(int **A, int n)
{
    printf("La matriz es: \n");

    for(i = 0; i < n; i++)
    {
        printf("(");
        for(j = 0; j < n; j++)
        {
            if( ((j+1) % n) == 0)
            {
                printf("%d)\n", A[i][j]);
            }
            else
            {
                printf("%d ", A[i][j]);
            }
        }
    }
}

int suma_matriz_dim(int **A, int n)
{
    int total_m = 0;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(j != i)
            {
                total_m += A[i][j];
            }
        }
    }

    return total_m;
}


int main()
{
    // Ejercicio 9.5
    int matriz_1[filas_3][columnas_4];

    leer_filas(&matriz_1[0][0]);

    imprimir_columnas(matriz_1);

    // Ejercicio 9.6
    int matriz_2[filas_m][filas_m];

    generar_matriz(&matriz_2[0][0]);

    imprimir_matriz(matriz_2);

    printf("El valor de la suma de la matriz sin la diagonal es: %d\n", suma_matriz(matriz_2));

    // ejercicio 9.6 dinamico
    int **matriz_dim, n;

    printf("Ingrese el largo de la matriz: ");
    scanf("%d", &n);

    matriz_dim = crear_matriz_dinam(n);

    imprimir_matriz_dim(matriz_dim, n);

    printf("El valor de la suma de la matriz sin la diagonal es: %d\n", suma_matriz_dim(matriz_dim, n));

    return 0;
}