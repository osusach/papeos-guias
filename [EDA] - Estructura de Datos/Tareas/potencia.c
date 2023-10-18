#include <stdio.h>

long long int potencia_suma(long long int a, long long int b)
{
    long long int i, j, resultado = 0, aux;
    for(i = 1; i < b; i++)
    {
        if (i == 1)
        {
            for(j = 0; j < a; j++)
            {
                resultado += a;
            }
        }
        else
        {
            for(j = 1; j < a; j++)
            {
                resultado += aux;
            }
        }
        aux = resultado;
    }
    return resultado;
}

void main()
{
    long long int num1, num2, resultado;

    printf("Ingrese 2 numeros separados por espacio: ");
    scanf("%llu %llu", &num1, &num2);

    resultado = potencia_suma(num1, num2);

    printf("%llu elevado a %llu es %llu", num1, num2, resultado);
}