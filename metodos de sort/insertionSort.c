#include <stdio.h>

// O Insertion Sort é um algoritmo de ordenação que constrói a lista ordenada gradualmente, 
// um elemento por vez. Ele percorre a lista, e para cada elemento, o insere na posição 
// correta em relação aos elementos anteriores, movendo os maiores elementos para a direita.

// Principais pontos:

// Complexidade: O(n²) no pior caso e no médio, mas O(n) no melhor caso (quando a lista já está quase ordenada).
// Estável: mantém a ordem relativa de elementos iguais.
// Eficiente para listas pequenas ou quase ordenadas.

int main() {
    int myArray[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int n = sizeof(myArray) / sizeof(myArray[0]);

    for (int i = 1; i < n; i++) {
        int insertIndex = i;
        int currentValue = myArray[i];
        int j = i - 1;

        while (j >= 0 && myArray[j] > currentValue) {
            myArray[j + 1] = myArray[j];
            insertIndex = j;
            j--;
        }
        myArray[insertIndex] = currentValue;
    }

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", myArray[i]);
    }

    return 0;
}