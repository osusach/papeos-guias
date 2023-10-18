#include <stdio.h>
#include <string.h>

struct producto
{
    char nombre[50];
    int precio;
    int cantidad;
};

int main()
{
    struct producto productos[10];
    int i, opcion = 1, eleccion;
    char name[50];

    for(i = 0; i < 10; i++)
    {
        strcpy(productos[i].nombre, "Sin producto");
        productos[i].precio = 0;
        productos[i].cantidad = 0;
    }

    while((opcion == 1 || 2 || 3) && (opcion != 4))
    {
        printf("1) Dar de alta un producto nuevo.\
        \n2) Buscar un producto por su nombre\
        \n3) Modificar el stock y precio de un producto dado.\
        \n4) salir\n\n");

        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        printf("\n");

        if(opcion == 1)
        {
            for(i = 0; i < 10; i++)
            {
                printf("%d) %s %d %d\n", i+1,productos[i].nombre, productos[i].precio, productos[i].cantidad);
            }

            printf("Que producto quiere eliminar?\n");
            scanf("%d", &eleccion);
            eleccion--;

            strcpy(productos[eleccion].nombre, "Sin producto");
            productos[eleccion].precio = 0;
            productos[eleccion].cantidad = 0;
        }
        else if(opcion == 2)
        {

            printf("Que producto quiere buscar?\n");
            scanf("%s", &name);

            for(i = 0; i < 10; i++)
            {
                if(strcmp(name, productos[i].nombre) == 0)
                {
                    printf("%s %d %d\n", productos[i].nombre, productos[i].precio, productos[i].cantidad);
                }
            }
        }
        else if(opcion == 3)
        {
            for(i = 0; i < 10; i++)
            {
                printf("%d) %s %d %d\n", i+1,productos[i].nombre, productos[i].precio, productos[i].cantidad);
            }

            printf("Que producto quiere actualizar?\n");
            scanf("%d", &eleccion);
            eleccion--;

            printf("Nuevo nombre: ");
            scanf("%s", &name);
            strcpy(productos[eleccion].nombre, name);

            printf("Nuevo precio: ");
            scanf("%d", &productos[eleccion].precio);

            printf("Nuevo cantidad: ");
            scanf("%d", &productos[eleccion].cantidad);
        }
    }   
    return 0;
}
