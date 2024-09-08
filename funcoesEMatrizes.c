#include <stdio.h>

void funcaoPrint(int matriz[][3]);
void funcaoRead(int matriz[][3]);
void quicksort(int array[], int low, int high);
int partition(int array[], int low, int high);
void matrizParaArray(int matriz[][3], int array[]);
void arrayParaMatriz(int array[], int matriz[][3]);

int main(void)
{
    int matriz[3][3];
    int array[9]; 
    
    funcaoRead(matriz);
    matrizParaArray(matriz, array);
    quicksort(array, 0, 8);
    arrayParaMatriz(array, matriz);
    funcaoPrint(matriz);

    return 0;
}

void funcaoPrint(int matriz[][3])
{
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 3; j++)
        {
            printf("%i ", matriz[i][j]);
        }
    }
    printf("\n");  
}

void funcaoRead(int matriz[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Escreva um numero para a posicao [%i][%i] da matriz: ", i, j);
            scanf("%d", &matriz[i][j]);
        }
    }
}

void quicksort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);
        quicksort(array, low, pi - 1);
        quicksort(array, pi + 1, high);
    }
}

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

void matrizParaArray(int matriz[][3], int array[])
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            array[k++] = matriz[i][j];
        }
    }
}

void arrayParaMatriz(int array[], int matriz[][3])
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matriz[i][j] = array[k++];
        }
    }
}
