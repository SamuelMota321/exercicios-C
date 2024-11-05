#include <stdio.h>

int main()
{
    int i, a[3];
    printf("digite 3 numeros: \n");

    for (i = 0; i < 3; i++)
    {
        scanf("%d", &a[i]);
    }
    int menor = a[0];

    for (i = 0; i < 3; i++)
    {
        if (menor > a[i])
        {
            menor = a[i];
        }
    }
    printf("o menor valor digitado e: %d\n", menor);
}
