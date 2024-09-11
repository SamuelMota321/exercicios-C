#include <stdio.h>
#include <stdlib.h>

// possui complexidade de tempo O(n) considerando o pior
// casos, mas a sua média de complexidade é em O(log n).
// isso faz com que essa estrutura tenha uma complexidade
// extremamente parecida com as árvores balanciadas e
// uma complecidade igual a de uma árvore binária, porém
// de mais fácil implementação

typedef struct Node
{
    int key;
    struct Node **next;
} Node;

typedef struct SkipList
{
    int maxLevel;
    float nodeF;      // fração do nó que será usada no sorteio para
    int currentLevel; // definir quantos níveis um novo nó tem
    struct Node *start;
} SkipList;

SkipList *createSkipList(int maxLevel, float nodeF);
Node *createNode(int key, int currentLevel);
void freeSkipList(SkipList *skipList);
int searchSkipList(SkipList *skipList, int key);
int insertAtSkipList(SkipList *skipList, int key);
int drawLevel(SkipList *skipList);
int removeNode(SkipList *skipList, int key);

int main(void)
{
    SkipList *teste = NULL;
    teste = createSkipList(3, 0.5);
    insertAtSkipList(&teste, 10);

    return 0;
}

SkipList *createSkipList(int maxLevel, float nodeF)
{
    SkipList *newSkipList = (SkipList *)malloc(sizeof(SkipList));
    if (newSkipList != NULL)
    {
        newSkipList->maxLevel = maxLevel;
        newSkipList->nodeF = nodeF;
        newSkipList->currentLevel = 0;
    }

    newSkipList->start = createNode(-1, maxLevel);

    return newSkipList;
}

Node *createNode(int key, int currentLevel)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode != NULL)
    {
        newNode->key = key;
        newNode->next = malloc((currentLevel + 1) * sizeof(Node));
        for (int i = 0; i < (currentLevel + 1); i++)
            newNode->next[i] == NULL;
    }
    return newNode;
}

void freeSkipList(SkipList *skipList)
{
    if (skipList == NULL)
        return;

    Node *temp, *current;
    current = skipList->start->next[0];
    while (current != NULL)
    {
        temp = current;
        current = current->next[0];
        free(temp->next);
        free(temp);
    }
    free(skipList->start);
    free(skipList);
}

int searchSkipList(SkipList *skipList, int key)
{
    if (skipList == NULL)
        return;

    Node *current = skipList->start;
    for (int i = skipList->currentLevel; i >= 0; i--)
        while (current->next[i] != NULL && current->next[i]->key < key)
            current = current->next[i];

    current = current->next[0];

    if (current != NULL && current->key == key)
        return 1;
    else
        return 0;
}

int insertAtSkipList(SkipList *skipList, int key)
{
    if (skipList == NULL)
        return 0;

    Node *current = skipList->start,
         **temp = malloc((skipList->maxLevel + 1) * sizeof(Node));

    for (int i = 0; i <= skipList->maxLevel; i++)
        temp[i] = NULL;

    for (int i = skipList->currentLevel; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->key < key)
            current = current->next[i];

        temp[i] = current;
    }
    current = current->next[0];
    if (current == NULL || current->key != key)
    {
        int newLevel = drawLevel(skipList);
        Node *newNode = createNode(key, newLevel);
        if (newNode == NULL)
        {
            free(temp);
            return 0;
        }

        if (newLevel > skipList->currentLevel)
        {
            for (int i = 0; i <= newLevel; i++)
                temp[i] = skipList->start;
            skipList->currentLevel = newLevel;
        }

        for (int i = 0; i <= newLevel; i++)
        {
            newNode->next[i] = temp[i]->next[i];
            temp[i]->next[i] = newNode;
        }

        free(temp);
        return 1;
    }
}

int drawLevel(SkipList *skipList)
{
    float random = (float)rand() / RAND_MAX;
    int level = 0;
    while (random < skipList->nodeF && level < skipList->maxLevel)
    {
        level++;
        random = (float)rand() / RAND_MAX;
    }
    return level;
}

int removeNode(SkipList *skipList, int key)
{
    if (skipList == NULL)
        return 0;

    Node *current = skipList->start,
         **temp = malloc((skipList->maxLevel) * sizeof(Node));
    for (int i = 0; i < skipList->maxLevel; i++)
        temp[i] = NULL;

    for (int i = skipList->currentLevel; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->key < key)
            current = current->next[i];
        temp[i] = current;
    }
}