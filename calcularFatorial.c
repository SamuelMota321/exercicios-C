#include <stdio.h>

int main()
{
    int count = 1;
    int fat = 1;
    int num;
    printf("digite um numero para calcular o seu fatorial: ");
    scanf(" %i", &num);

    while (count <= num)
    {
        fat *= count;
        ++count;
    }

    printf("O numero fatorial e igual a: %i", fat);
    return 0;
}