#include <stdio.h>
#include <stdlib.h>

// valores globales para iterar
int i;
int j;

// funcion que abre el archivo y verifica si fue abierto corretamente
FILE *abrir_archivo(char *nombre_archivo, char *modo)
{
    FILE *arch = fopen(nombre_archivo, modo);

    // se verifica si se abre
    if(arch == NULL)
    {
        printf("Nombre incorrecto o el archivo no existe\n");
        return NULL;
    }

    printf("Archivo abierto correctamente\n");
    return arch;
}

// funcion que lee el archivo y lo guarda en una matriz char
// a su vez guarda los valores del largo y el alto para usarlos en el main
char **cargar_laberinto(FILE *arch , int *a, int *b)
{
    char **matriz;
    int largo, alto;
    fscanf(arch, "%d %d", &alto, &largo);
    *a = alto, *b = largo;

    matriz = (char**)malloc(sizeof(char*) * alto);
    for(i = 0; i <= alto; i++)
    {
        matriz[i] = (char*)malloc(sizeof(char) * largo);
    }

    for(i = 0; i <= alto; i++)
    {
        // para corregir el salto de linea restante al leer las medidas
        getc(arch);
        for(j = 0; j <= largo; j++)
        {
            // se le agregan una columna y una fila al final para evitar
            // errores con los indices despues
            if(j == largo || i == alto)
            {
                matriz[i][j] = 'x';
            }
            else
            {
                matriz[i][j] = fgetc(arch);
            }
        }
    }

    printf("laberinto cargado con exito\n");
    return matriz;
}

int *encontrar_entrada(char **matriz, int alto, int largo)
{
    int *pos;
    pos = (int*)malloc(sizeof(int) * 2);

    for(i = 0; i < alto; i++)
    {
        for(j = 0; j < largo; j++)
        {
            if (matriz[i][j] == 'e')
            {
                pos[0] = i;
                pos[1] = j;
            }
        }
    }

    return pos;
}

// en esta funcion se intentara buscar la salida colocando un * en cada o recorrido
char busqueda_salida(char **matriz,int x, int y)
{ 
    int cord_x, cord_y;
    char salida;

    // recorrido
    if(matriz[x][y + 1] == 'o')
    {
        cord_x = x;
        cord_y = y + 1;
        matriz[x][y + 1] = '*';
        salida = busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x + 1][y] == 'o')
    {
        cord_x = x + 1;
        cord_y = y;
        matriz[x +  1][y] = '*';
        salida = busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x][y - 1] == 'o')
    {
        cord_x = x;
        cord_y = y - 1;
        matriz[x][y - 1] = '*';
        salida = busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x - 1][y] == 'o')
    {
        cord_x = x - 1;
        cord_y = y;
        matriz[x - 1][y] = '*';
        salida = busqueda_salida(matriz, cord_x, cord_y);
    }
    // casos donde regresa a la entrada
    else if(matriz[x][y + 1] == 'e')
    {
        cord_x = x;
        cord_y = y + 1;
        busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x + 1][y] == 'e')
    {
        cord_x = x + 1;
        cord_y = y;
        busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x][y - 1] == 'e')
    {
        cord_x = x;
        cord_y = y - 1;
        busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x - 1][y] == 'e')
    {
        cord_x = x - 1;
        cord_y = y;
        busqueda_salida(matriz, cord_x, cord_y);
    }
    // casos donde encuentra la salida
    else if(matriz[x][y + 1] == 's')
    {
        return 's';
    }
    else if(matriz[x + 1][y] == 's')
    {
        return 's';
    }
    else if(matriz[x][y - 1] == 's')
    {
        return 's';
    }
    else if(matriz[x - 1][y] == 's')
    {
        return 's';
    }
    // casos donde se tiene que regresar
    else if(matriz[x][y - 1] == '*')
    {
        cord_x = x;
        cord_y = y - 1;
        busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x - 1][y] == '*')
    {
        cord_x = x - 1;
        cord_y = y;
        busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x][y + 1] == '*')
    {
        cord_x = x;
        cord_y = y + 1;
        busqueda_salida(matriz, cord_x, cord_y);
    }
    else if(matriz[x + 1][y] == '*')
    {
        cord_x = x + 1;
        cord_y = y;
        busqueda_salida(matriz, cord_x, cord_y);
    }
    else
    {
        return 'n';
    }
}

int main(int argc, char *argv[])
{
    FILE *arch;
    char **matriz;
    int alto, largo;
    int *pos_entrada;
    char salida;


    arch = abrir_archivo(argv[2], "r");

    // en caso de no existir el archivo se termina el programa
    if(arch == NULL)
    {
        return 0;
    }
    
    matriz = cargar_laberinto(arch, &alto, &largo);
    pos_entrada = encontrar_entrada(matriz, alto, largo);

    salida = busqueda_salida(matriz, pos_entrada[0], pos_entrada[1]);

    if(salida == 's')
    {
        printf("Hay salida y el recorrido es:\n");

        for(i = 0; i < alto; i++)
        {
            for(j = 0; j < largo; j++)
            {
                printf("%c", matriz[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("El laberinto no tiene solucion");
    }
    
    return 0;
}