#include <stdio.h>

void imprimaMensagem(void)
{
    printf("Ola mundo!");
}

float calcularAreaRetangulo(float x, float y)
{
    float area = x * y;
    return area;
}

int main(void)
{
    float calcularAreaRetangulo(float x, float y);
    float num1, num2;

    printf("Digite a altura do retangulo ");
    scanf("%f", &num1);
    printf("Digite a largura do retangulo ");
    scanf("%f", &num2);
    float area = calcularAreaRetangulo(num1, num2);
    printf("A area do retangulo e igual a %.2f ", area);

    return 0;
}