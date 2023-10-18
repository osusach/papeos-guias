#include <stdio.h>

int modulo_resta(int a, int b)
{
    while(a >= b)
    {
        a -= b;
    }
    return a;
}

void main()
{
    int num1, num2, modulo;

    printf("Ingrese 2 numeros separados por espacio: ");
    scanf("%d %d", &num1, &num2);

    modulo = modulo_resta(num1, num2);

    printf("El modulo de %d/%d es %d", num1, num2, modulo);
}
