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

void escribir_archivo(FILE *arch)
{
    int num = 4;
    int edad = 20, i;

    fprintf(arch, "Hola mundo!!.. estoy escribiendo en este archivo ");
    fprintf(arch, "Cantidad de datos: %d\n", num);

    for(i = 1; i <= num; i++)
    {
        fprintf(arch, "Edad y nombre de persona %d:\n", i);
        fprintf(arch, "\t%d años y nombre%d\n\n", edad, i);
        edad++;
    }
    fclose(arch);

    printf("Archivo escrito correctamente");
}

int main(int argc, char *argv[])
{
    FILE *arch_s = abrir_archivo(argv[2], "w");

    escribir_archivo(arch_s);
    
    fclose(arch_s);

    return 0;
}