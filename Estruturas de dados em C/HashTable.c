#include <stdio.h>
#include <stdlib.h>

// a tabela hash é uma estutura usada em casos quando é
// necessário uma busca rápida de um conjuto de elementos
// tendo uma complexidade O(1) constante para busca
// geralmente na tabela hash não é feito muitas insersões
// e remoções, costuma-se saber qual será tamanho do
// conjunto de dados

// tabela hash linear com vetor

// para um vetor de 15 elementos  usamos a seguinte formula
// para descobrir o tamanho da tabela
// 2 * 15 = 30
// observase que não usaremos o número 30, mas sim o primo
// mais próximo, podendo ser 29 ou 31
#define SIZE 31

int hashFunction(int key);
void insert(int table[], int data);
int search(int table[], int key);
void printTable(int table[]);

int main(void)
{
    int table[SIZE] = {0};

    return 0;
}

int hashFunction(int key)
{
    return key % SIZE;
}

void insert(int table[], int data)
{
    int id = hashFunction(data);
    while (table[id] != 0)
        id = hashFunction(id + 1);
    table[id] = data;
}

int search(int table[], int key)
{
    int id = hashFunction(key);
    while (table[id] != 0)
        if (table[id] == key)
            return table[id];
        else
            id = hashFunction(id + 1);
}

void printTable(int table[])
{
    int i;
    for(i = 0; i < SIZE; i++ )
    {
        printf("{index: %d, key: %d}", i, table[i]);
    }
}
