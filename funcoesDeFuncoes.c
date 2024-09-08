#include <stdio.h>

int main(void)
{
    float a, b, soma;
    float somaDoisNumeros(float num1, float num2);
    printf("digite dois numeros: ");
    scanf("%f", &a);
    scanf("%f", &b);

    soma = somaDoisNumeros(a, b);
    printf("A soma e igual a %.2f", soma);

    return 0;
}

float somaDoisNumeros(float num1, float num2)
{
    float valorAbsoluto(float x);

    if (num1 < 0)
    {
        num1 = valorAbsoluto(num1);
    }
    if (num2 < 0)
    {
        num2 = valorAbsoluto(num2);
    }

    return num1 + num2;
}

float valorAbsoluto(float x)
{
    return x * -1;
}