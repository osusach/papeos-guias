#include <stdio.h>

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

void mostrar_contenido_archivo(FILE *arch)
{
    char caracter;
    
    while((caracter = getc(arch)) != EOF)
    {
        printf("%c", caracter);
    }
}

int main(int argc, char *argv[])
{
    FILE *arch;

    arch = abrir_archivo(argv[2], "r");

    mostrar_contenido_archivo(arch);

    fclose(arch);

    return 0;
}