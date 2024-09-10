#include <stdio.h>
#include <stdlib.h>

// possui complexidade de tempo O(n) para operações 
// de busca e pesquisa, O(1) para operações de inserção
// e exclusão e O(n) para armazenamento

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;

} Node;

Node *createNode(int data);
void insertAtHead(Node **head, int data);
void insertAtTail(Node **head, int data);
void deleteNode(Node **head, int data);
void printList(Node *head);

int main(void)
{
    Node *head = NULL;

    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtHead(&head, 30);
    insertAtHead(&head, 25);
    insertAtTail(&head, 30);
    insertAtTail(&head, 40);
    insertAtTail(&head, 50);

    printf("Lista apos insercoes:\n");
    printList(head);

    deleteNode(&head, 30);

    printf("Lista apos deletar o no com valor 30:\n");
    printList(head);
    return 0;
}

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertAtHead(Node **head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertAtTail(Node **head, int data)
{
    struct Node *newNode = createNode(data);
    struct Node *temp = *head;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteNode(Node **head, int data)
{
    if (*head == NULL)
    {
        return;
    }

    Node *temp = *head;
    while (temp != NULL && temp->data != data)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return;
    }

    if (*head == temp)
    {
        *head = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    free(temp);
}

void printList(Node *head)
{
    Node *temp = head;

    printf("cabeca");
    while (temp != NULL)
    {
        printf(" %d ", temp->data);
        temp = temp->next;
    }
    printf("cauda\n");
    free(temp);
}
