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

void escribir_imprimir_archivo(FILE *arch_e, FILE *arch_s)
{
    char linea[50];

    while(fgets(linea, 50, arch_e) != NULL)
    {
       archuts(linea, arch_s);
       printf("%s", linea);
    }
}

int main(int argc, char *argv[])
{
    FILE *arch_e = abrir_archivo(argv[2], "r");
    FILE *arch_s = abrir_archivo(argv[3], "w");

    escribir_imprimir_archivo(arch_e, arch_s);

    fclose(arch_e);
    fclose(arch_s);

    return 0;
}