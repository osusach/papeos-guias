#include <stdio.h>
#include <stdlib.h>

FILE *abrir_archivo(char nombre_archivo[50], char *modo)
{
    FILE *arch = fopen(nombre_archivo, modo);

    if(arch == NULL)
    {
        printf("Nombre incorrecto o el archivo no existe\n");
        return NULL;
    }

    printf("Archivo abierto correctamente\n");

    return arch;
}

void imprimir_con_formato(FILE *arch)
{
    char nombre[30], estado[20];
    int edad;

    while(fscanf(arch, "%s %d %s", nombre, &edad, estado) != EOF)
    {
       fscanf(arch, "%s %d %s", nombre, &edad, estado);
       printf("Esta es persona es %s con edad: %d y estado: %s\n\n", nombre, edad, estado);
    }
}

int main(int argc, char *argv[])
{
    FILE *arch = abrir_archivo(argv[2], "r");

    imprimir_con_formato(arch);

    fclose(arch);

    return 0;
}