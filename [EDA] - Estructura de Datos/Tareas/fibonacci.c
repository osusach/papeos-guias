#include <stdio.h>
#include <time.h>

long long int fibonacci_i(int numero)
{
    int f0 = 0, f1 = 1, i;
    long long int fibona;

    if(numero <= 0)
    {
        return 0;
    }
    else if(numero == 1)
    {
        return 1;
    }
    else
    {
        for(i = 1; i < numero; i++)
        {
            fibona = f0 + f1;
            f0 = f1;
            f1 = fibona;
        }
        return fibona;
    }
}

long long int fibonacci_r(int numero)
{
    long long int fibona;

    if(numero <= 0)
    {
        return 0;
    }
    else if(numero == 1)
    {
        return 1;
    }
    else
    {
        return fibonacci_r(numero - 1) + fibonacci_r(numero - 2);
    }
}

int main()
{
    time_t start, end, start_1, end_1;
    int numero;
    long long int fibo_r, fibo_i;

    printf("Ingrese un numero: ");
    scanf("%d", &numero);

    start = time(NULL);
    
    fibo_i = fibonacci_i(numero);
    printf("La serie de fibonacci iterativa de %d es %llu\n", numero, fibo_i);

    end = time(NULL);
    printf("El tiempo de demora es de %.4f\n", difftime(end, start));

    start_1 = time(NULL);
    
    fibo_r = fibonacci_r(numero);
    printf("La serie de fibonacci recursiva de %d es %llu\n", numero, fibo_r);

    end_1 = time(NULL);
    printf("El tiempo de demora es de %.4f\n", difftime(end_1, start_1));

    return 0;
}