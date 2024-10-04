#include <stdio.h>

// O Bubble Sort é um algoritmo de ordenação simples que compara dois elementos adjacentes de uma lista e os
// troca de lugar se estiverem na ordem errada. Esse processo é repetido várias vezes até que a lista esteja ordenada. O nome "bubble" (bolha)
// vem do fato de que os maiores elementos "flutuam" para o topo (final) da lista a cada iteração.

// Principais pontos:
// Complexidade: melhor caso: O(n) media e pior caso: O(n²), onde n é o número de elementos.
// Estável: mantém a ordem relativa de elementos iguais.
// Simples de implementar, mas ineficiente para listas grandes.

int main()
{
    int my_array[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int n = sizeof(my_array) / sizeof(my_array[0]);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (my_array[j] > my_array[j + 1])
            {
                int temp = my_array[j];
                my_array[j] = my_array[j + 1];
                my_array[j + 1] = temp;
            }
        }
    }

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    return 0;
}