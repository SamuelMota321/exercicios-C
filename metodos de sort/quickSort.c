#include <stdio.h>

// O QuickSort é um algoritmo de ordenação eficiente que usa o conceito de "dividir e conquistar". 
// Ele seleciona um elemento como pivô, reorganiza os elementos para que os menores fiquem à 
// esquerda e os maiores à direita, e então aplica o mesmo processo recursivamente às sublistas.

// Principais pontos:

// Complexidade: O(n log n) no melhor e na média, mas O(n²) no pior caso (quando o pivô é mal escolhido).
// Não é estável: pode alterar a ordem relativa de elementos iguais.
// Muito eficiente para grandes listas e é amplamente usado na prática.

void quicksort(int array[], int low, int high);
int partition(int array[], int low, int high);

int main() {
    int myArray[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int n = sizeof(myArray) / sizeof(myArray[0]);

    quicksort(myArray, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", myArray[i]);
    }
    return 0;
}

void quicksort(int array[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quicksort(array, low, pivotIndex - 1);
        quicksort(array, pivotIndex + 1, high);
    }
}

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}
