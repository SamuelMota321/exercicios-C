#include <stdio.h>

int inverteNum(int cifra, int num)
{
    do
    {
        cifra = num % 10;
        printf("%i", cifra);
        num /= 10;
    } while (num != 0);

    return 0;
}

int main()
{
    int num;
    int cifra = 0;

    printf("Digite um numero inteiro: \n");
    scanf("%i", &num);

    if (num >= 0)
    {
        inverteNum(cifra, num);
    }
    else if (num < 1)
    {
        num = num * -1;
        printf("-");
        inverteNum(cifra, num);
    }
    return 0;
}