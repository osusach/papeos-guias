#include <stdio.h>

void puntero(int *a, int *b)
{
    int i  = 10;

    for(i; i > 0; i--)
    {
        *a += *b;
    }
}

void main()
{
    int c = 0;
    int *a = &c, b = 6;

    printf("este es a:%d este es b:%d\n", c, b);

    puntero(a, &b);

    printf("este es a:%d este es b:%d", c, b);
}