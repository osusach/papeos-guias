#include <stdio.h>

// Funciones del ejercicio 1

void elevado(int a, int b)
{
    float eleva = 1;
    int i;

    if(b > 0)
    {
        for(i=0; i<b; i++)
        {
            eleva = eleva * a;
        }
    }
    else if(b < 0)
    {
        for(i=0; i<-b; i++)
        {
            eleva = eleva * a;
        }
        eleva = 1 / eleva;
    }

    printf("\n%d elevado a %d es %.4f\n\n", a, b, eleva);
}

void division(int a, int b)
{
    float div, divisor = a, denominador = b; 

    div = divisor/denominador;
    
    printf("La division entre %d y %d es %.4f\n\n", a, b, div);
}

void fib(int a, int b)
{
    int f1 = 0, f2 = 1, menor, fibonacci;
    int i;

    if(a < b)
    {
        menor = a;
    }
    else
    {
        menor = b;
    }

    if(menor <= 0)
    {
        fibonacci = 0;
    }
    else if(menor == 1)
    {
        fibonacci = 1;
    }
    else
    {
        for(i = 2; i <= menor; i++)
        {
            fibonacci = f2 + f1;
            f1 = f2;
            f2 = fibonacci;
        }
    }
    printf("La serie de fibonacci del menor de los elementos(%d) es %d\n\n", menor, fibonacci);
}

// Funciones del ejercicio 2

void mayor(int a[])
{
    int indice = 0, i, pedido;

    printf("Ingrese un valor entre 1-20: ");
    scanf("%d", &pedido); 
    pedido--;

    printf("Los mayores que el numero pedido (%d) son:\n", a[pedido]);

    for(i = 0; i < 20; i++)
    {
        if(a[pedido] < a[i])
        {
            printf("%d\n", a[i]);
        }
    }
}

void prom(int a[])
{
    int i;
    float promedio = 0;

    for(i = 0; i < 20; i++)
    {
        promedio = promedio + a[i]; 
    }

    promedio = promedio / 20;
    printf("\n\nel promedio de los elementos de A %0.3f\n\n", promedio);
}

void esPar(int a[])
{
    int indice, buscar, verificar;

    printf("Ingrese que valor busca entre 1 a 20: ");
    scanf("%d", &buscar);

    switch(buscar){
        case 1:
            indice = 1;
            break;
        case 2:
            indice = 2;
            break;
        case 3:
            indice = 3;
            break;
        case 4:
            indice = 4;
            break;
        case 5:
            indice = 5;
            break;
        case 6:
            indice = 6;
            break;
        case 7:
            indice = 7;
            break;
        case 8:
            indice = 8;
            break;
        case 9:
            indice = 9;
            break;
        case 10:
            indice = 10;
            break;
        case 11:
            indice = 11;
            break;
        case 12:
            indice = 12;
            break;
        case 13:
            indice = 13;
            break;
        case 14:
            indice = 14;
            break;
        case 15:
            indice = 15;
            break;
        case 16:
            indice = 16;
            break;
        case 17:
            indice = 17;
            break;
        case 18:
            indice = 18;
            break;
        case 19:
            indice = 19;
            break;
        case 20:
            indice = 20;
            break;
        default:
            indice = 1;
    }
    indice--;

    if(a[indice] % 2 == 0)
    {
        verificar = 1;
    } 
    else 
    {
        verificar = 0;
    }
    printf("1 es par y 0 impar y este numero(%d) es: %d", a[indice], verificar);
}

void main() 
{
    // Variables comunes
    int i;

    // Variables ejercicio 1
    int num1, num2;

    // Variables ejercicio 2
    int lista[20];

    // Ejercicio 1

    printf("Ejercicio 1\n\n");

    // obtener los numeros

    printf("Ingrese un numero: ");
    scanf("%d", &num1);

    printf("Ingrese otro numero: ");
    scanf("%d", &num2);

    // el primer numero elevado al segundo numero

    elevado(num1, num2);

    // division con presicion de 4 decimales entre los numeros

    division(num1, num2);

    // serie de fibonacci del menor de los numeros

    fib(num1, num2);
    

    // Ejercicio 2

    printf("Ejercicio 2\n\n");

    for(i=0; i<20; i++)
    {
        printf("Ingrese el valor n%d: ", i+1);
        scanf("%d", &lista[i]);
    }

    // numeros mayores que el valor pedido

    mayor(lista);

    // promedio de los elementos de A

    prom(lista);

    // usar switch para verificar si es par o impar

    esPar(lista);
}
