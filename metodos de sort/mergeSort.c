#include <stdio.h>

// O MergeSort é um algoritmo de ordenação que também segue o paradigma de "dividir e conquistar".
//  Ele divide recursivamente a lista ao meio até que cada sublista tenha um único elemento, e 
//  então combina (merge) essas sublistas ordenadas para formar uma lista ordenada maior.

// Principais pontos:

// Complexidade: O(n log n) em todos os casos (melhor, médio e pior).
// Estável: mantém a ordem relativa de elementos iguais.
// Consome mais memória devido ao uso de listas auxiliares durante o processo de "merge"

void mergeSort(double arr[], int start, int end);
void merge(double arr[], int start, int mid, int end);

int main() {
    double unsortedArr[] = {3, 7, 6, -10, 15, 23.5, 55, -13};
    int size = sizeof(unsortedArr) / sizeof(unsortedArr[0]);

    mergeSort(unsortedArr, 0, size - 1);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%.1f ", unsortedArr[i]);
    }
    printf("\n");

    return 0;
}

void mergeSort(double arr[], int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void merge(double arr[], int start, int mid, int end) {
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    double left[n1], right[n2];

    for (i = 0; i < n1; i++)
        left[i] = arr[start + i];
    for (j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = start;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}