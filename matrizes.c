#include <stdio.h>

int main(void)
{
    int matriz[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // leitura de matriz
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 3; j++)
        {
            printf("%i ", matriz[i][j]);
        }
    }
}