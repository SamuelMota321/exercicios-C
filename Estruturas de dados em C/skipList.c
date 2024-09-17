#include <stdio.h>
#include <stdlib.h>

// possui complexidade de tempo O(n) considerando o pior
// casos, mas a sua média de complexidade é em O(log n).
// isso faz com que essa estrutura tenha uma complexidade
// extremamente parecida com as árvores balanciadas e
// uma complecidade igual a de uma árvore binária, porém
// de mais fácil implementação

#define MAX_LEVEL 6
typedef struct Node
{
    int key;
    struct Node **next;
} Node;

typedef struct SkipList
{
    int level;          
    struct Node *header; 
} SkipList;


Node *createNode(int key, int level);
SkipList *createSkipList();
int randomLevel();
void insert(SkipList *list, int key);
Node *search(SkipList *list, int key);
void delete(SkipList *list, int key);
void printList(SkipList *list);


int main()
{

    SkipList *list = createSkipList();

    insert(list, 3);
    insert(list, 6);
    insert(list, 7);
    insert(list, 9);
    insert(list, 12);
    insert(list, 19);
    insert(list, 13);
    insert(list, 14);
    insert(list, 15);
    insert(list, 16);
    insert(list, 17);
    insert(list, 18);
    insert(list, 11);
    insert(list, 1);

    printList(list);

    int key = 6;
    Node *node = search(list, key);
    if (node)
    {
        printf("Found key: %d\n", key);
    }
    else
    {
        printf("Key not found: %d\n", key);
    }

    delete (list, 3);
    delete (list, 7);
    delete (list, 13);

    printList(list);

    return 0;
}

Node *createNode(int key, int level)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = (Node **)malloc(sizeof(Node *) * (level + 1));

    for (int i = 0; i <= level; i++)
    {
        newNode->next[i] = NULL;
    }

    return newNode;
}

SkipList *createSkipList()
{
    SkipList *list = (SkipList *)malloc(sizeof(SkipList));
    list->level = 0;
    list->header = createNode(-1, MAX_LEVEL);

    return list;
}

int randomLevel()
{
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL)
    {
        level++;
    }
    return level;
}

void insert(SkipList *list, int key)
{
    Node *current = list->header;
    Node *update[MAX_LEVEL + 1];

    for (int i = list->level; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->key < key)
        {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current == NULL || current->key != key)
    {
        int newLevel = randomLevel();

        if (newLevel > list->level)
        {
            for (int i = list->level + 1; i <= newLevel; i++)
            {
                update[i] = list->header;
            }
            list->level = newLevel;
        }

        Node *newNode = createNode(key, newLevel);

        for (int i = 0; i <= newLevel; i++)
        {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }

        printf("Inserted key: %d\n", key);
    }
}

Node *search(SkipList *list, int key)
{
    Node *current = list->header;

    for (int i = list->level; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->key < key)
        {
            current = current->next[i];
        }
    }

    current = current->next[0];

    if (current != NULL && current->key == key)
    {
        return current;
    }

    return NULL;
}

void delete(SkipList *list, int key)
{
    Node *current = list->header;
    Node *update[MAX_LEVEL + 1];

    for (int i = list->level; i >= 0; i--)
    {
        while (current->next[i] != NULL && current->next[i]->key < key)
        {
            current = current->next[i];
        }
        update[i] = current;
    }

    current = current->next[0];

    if (current != NULL && current->key == key)
    {
        for (int i = 0; i <= list->level; i++)
        {
            if (update[i]->next[i] != current)
            {
                break;
            }
            update[i]->next[i] = current->next[i];
        }

        free(current);

        while (list->level > 0 && list->header->next[list->level] == NULL)
        {
            list->level--;
        }

        printf("Deleted key: %d\n", key);
    }
}

void printList(SkipList *list)
{
    printf("Skip List:\n");
    for (int i =list->level; i >= 0 ; i--)
    {
        Node *current = list->header->next[i];
        printf("Level %d: ", i);
        while (current != NULL)
        {
            printf("%d ", current->key);
            current = current->next[i];
        }
        printf("\n");
    }
}