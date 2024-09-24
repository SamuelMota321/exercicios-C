#include <stdio.h>
#include <stdlib.h>

// a tabela hash é uma estutura usada em casos quando é
// necessário uma busca rápida de um conjuto de elementos
// tendo uma complexidade O(1) constante para busca
// geralmente na tabela hash não é feito muitas insersões
// e remoções, costuma-se saber qual será tamanho do
// conjunto de dados

// tabela hash com lista encadeada
// também usa vetor, mas cada posição armazena uma lista
// encadeada

// para um vetor de 15 elementos  usamos a seguinte formula
// para descobrir o tamanho da tabela
// 2 * 15 = 30
// observase que não usaremos o número 30, mas sim o primo
// mais próximo, podendo ser 29 ou 31
#define SIZE 31

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    struct Node *init;
    int size;
} List;

// funções Lista
void initList(List *list);
void insertAtList(List *list, int data);

// funções hashtable
int hashFunction(int key);
void insert(int table[], int data);
int search(int table[], int key);
void delete(int table[], int key);
void printTable(int table[]);

int main(void)
{
    int table[SIZE] = {0},
        option,
        key;
    do
    {
        printf("Escolha uma opcao\n\t 0 - sair\n\t 1 - inserir\n\t 2 - buscar\n\t 3 - imprimir\n\t 4 - deletar\n");

        if (scanf("%d", &option) != 1)
        {
            printf("Entrada invalida. Por favor, insira um numero.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (option)
        {
        case 1:
            printf("digite um valor para ser inserido: ");
            scanf("%d", &key);
            insert(table, key);
            break;

        case 2:
            printf("Digite um valor para ser buscado na tabela: ");
            scanf("%d", &key);
            int result = search(table, key);
            if (result == 0)
                printf("Elemento nao encontrado\n");
            else
                printf("Foi encontrado o elemento %d\n", key);
            break;

        case 3:
            printTable(table);
            break;

        case 4:
            printf("Digite o valor para ser deletado: ");
            scanf("%d", &key);
            delete (table, key);
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (option != 0);

    return 0; // final do programa main
}

void initList(List *list)
{
    list->init = NULL;
    list->size = 0;
}

void insertAtList(List *list, int data)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode)
    {
        newNode->data = data;
        newNode->next = list->init;
        list->init = newNode;
        list->size++;
    }
    else
        printf("\nErro ao alocar memória!\n");
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
    printf("\nindicie gerada: %d\n", id);
    while (table[id] != 0)
    {
        if (table[id] == key)
            return table[id];
        else
            return id = hashFunction(id + 1);
    }
    return 0;
}

void delete(int table[], int key)
{
    int id = hashFunction(key);
    while (table[id] != key)
        id = hashFunction(id + 1);
    table[id] = 0;
}

void printTable(int table[])
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("{index: %d, key: %d}\n", i, table[i]);
    }
}
#include <stdio.h>
#include <stdlib.h>

// a tabela hash é uma estutura usada em casos quando é
// necessário uma busca rápida de um conjuto de elementos
// tendo uma complexidade O(1) constante para busca
// geralmente na tabela hash não é feito muitas insersões
// e remoções, costuma-se saber qual será tamanho do
// conjunto de dados

// tabela hash com lista encadeada
// também usa vetor, mas cada posição armazena uma lista
// encadeada

// para um vetor de 15 elementos  usamos a seguinte formula
// para descobrir o tamanho da tabela
// 2 * 15 = 30
// observase que não usaremos o número 30, mas sim o primo
// mais próximo, podendo ser 29 ou 31
#define SIZE 31

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    struct Node *init;
    int size;
} List;

// funções Lista
void initList(List *list);
void insertAtList(List *list, int data);
int searchOnList(List *list, int key);
void printList(List *list);

// funções hashtable
int hashFunction(int key);
void insert(int table[], int data);
int search(int table[], int key);
void delete(int table[], int key);
void printTable(int table[]);

int main(void)
{
    int table[SIZE] = {0},
        option,
        key;
    do
    {
        printf("Escolha uma opcao\n\t 0 - sair\n\t 1 - inserir\n\t 2 - buscar\n\t 3 - imprimir\n\t 4 - deletar\n");

        if (scanf("%d", &option) != 1)
        {
            printf("Entrada invalida. Por favor, insira um numero.\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (option)
        {
        case 1:
            printf("digite um valor para ser inserido: ");
            scanf("%d", &key);
            insert(table, key);
            break;

        case 2:
            printf("Digite um valor para ser buscado na tabela: ");
            scanf("%d", &key);
            int result = search(table, key);
            if (result == 0)
                printf("Elemento nao encontrado\n");
            else
                printf("Foi encontrado o elemento %d\n", key);
            break;

        case 3:
            printTable(table);
            break;

        case 4:
            printf("Digite o valor para ser deletado: ");
            scanf("%d", &key);
            delete (table, key);
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (option != 0);

    return 0; // final do programa main
}

void initList(List *list)
{
    list->init = NULL;
    list->size = 0;
}

void insertAtList(List *list, int data)
{
    Node *newNode = malloc(sizeof(Node));

    if (newNode)
    {
        newNode->data = data;
        newNode->next = list->init;
        list->init = newNode;
        list->size++;
    }
    else
        printf("\nErro ao alocar memória!\n");
}

int searchOnList(List *list, int key)
{
    Node *temp = list->init;
    while (temp != NULL && temp->data != key)
        temp = temp->next;
    if (temp)
        return temp->data;
    return 0;
}

void printList(List *list)
{
    Node *temp = list->init;
    printf("Tamanho da Lista: %d: ", list->size);
    while (temp != NULL)
    {
        printf("%d ->", temp->data);
        temp = temp->next;
    }
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
    printf("\nindicie gerada: %d\n", id);
    while (table[id] != 0)
    {
        if (table[id] == key)
            return table[id];
        else
            return id = hashFunction(id + 1);
    }
    return 0;
}

void delete(int table[], int key)
{
    int id = hashFunction(key);
    while (table[id] != key)
        id = hashFunction(id + 1);
    table[id] = 0;
}

void printTable(int table[])
{
    int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("{index: %d, key: %d}\n", i, table[i]);
    }
}