#include <stdio.h>

// O Selection Sort é um algoritmo de ordenação que divide a lista em duas partes: a parte ordenada e a não ordenada. 
// Em cada iteração, ele encontra o menor (ou maior) elemento da parte não ordenada e 
// o troca com o primeiro elemento dessa parte. Isso é repetido até que toda a lista esteja ordenada.

// Principais pontos:

// Complexidade: em todos os casos: O(n²), onde n é o número de elementos.
// Não é estável: pode alterar a ordem relativa de elementos iguais.
// Simples de entender e implementar, mas ineficiente para grandes listas.

int main() {
    int my_array[] = {64, 34, 25, 5, 22, 11, 90, 12};
    int n = sizeof(my_array) / sizeof(my_array[0]);

    for (int i = 0; i < n-1; i++) {
        int min_index = i;
        for (int j = i+1; j < n; j++) {
            if (my_array[j] < my_array[min_index]) {
                min_index = j;
            }
        }
        int min_value = my_array[min_index];
        for (int k = min_index; k > i; k--) {
            my_array[k] = my_array[k-1];
        }
        my_array[i] = min_value;
    }

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    return 0;
}