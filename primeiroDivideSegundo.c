#include <stdio.h>

int main()
{
    int num1;
    int num2;

    printf("digite um numero: ");
    scanf(" %i", &num1);
    printf("digite um outro numero : ");
    scanf(" %i", &num2);

    double div = num1 % num2;

    if (num1 == 0 || num2 == 0)
    {
        return printf("Nao e possivel realizar uma divisao por 0");
    }

    if (div == 0)
    {
        return printf("O numero 1 e divisivel pelo numero 2");
    }

    return printf("O numero 1 nao e divisivel pelo numero 2");
}