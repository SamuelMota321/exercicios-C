#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Função para inserir um novo nó no início da lista
void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Função para inserir um novo nó no final da lista
void insertAtTail(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Função para deletar um nó com um valor específico
void deleteNode(Node** head, int data) {
    Node* temp = *head;
    Node* prev = NULL;

    // Se o nó a ser excluído é o primeiro nó
    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }

    // Procurar o nó a ser excluído
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    // Se o nó não for encontrado
    if (temp == NULL) {
        printf("Valor não encontrado!\n");
        return;
    }

    // Desvincular o nó da lista e liberar memória
    prev->next = temp->next;
    free(temp);
}

// Função para imprimir todos os nós da lista
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Função principal para testar as operações
int main() {
    Node* head = NULL;

    // Inserindo alguns nós
    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtTail(&head, 30);
    insertAtTail(&head, 40);

    printf("Lista após inserções:\n");
    printList(head);

    // Deletando um nó
    deleteNode(&head, 20);

    printf("Lista após deletar o nó com valor 20:\n");
    printList(head);

    // Limpando a memória
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
