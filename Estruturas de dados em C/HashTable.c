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

void hashFuction(int table, int key);
void insert(int data);

int main(void)
{
    int table[SIZE] = {0};

    return 0;
}

void hashFuction(int table[], int key)
{
    return key % SIZE;
}

void insert(int data)
{
    int id = hashFuction(data);
    while (table[id] != 0)
        id = hashFucton(id + 1);
}