#include <stdio.h>

// Definição da estrutura da árvore binária de busca
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *insert1(Node *root, int data);
void insert2(Node **root, int data);
void insert3(Node **root, int data);
Node *search1(Node *root, int data);
Node *search2(Node *root, int data);
Node *delete(Node *root, int data);
void printInOrder(Node *root);
int height(Node *root);

int main(void)
{
    Node *root = NULL;
    Node *search = NULL;
    root = insert1(root, 50);
    insert2(&root, 30);
    insert3(&root, 70);
    insert2(&root, 20);
    insert3(&root, 40);
    insert2(&root, 60);
    insert3(&root, 80);
    insert3(&root, 90);

    printf("Raiz: %d Arvore em ordem:  ", root->data);
    printInOrder(root);
    printf("\n");
    // search = search1(root, 120);
    search = search2(root, 80);
    if (search)
        printf("Valor encontrado na busca: %d", search->data);
    else
        printf("Valor nao encontrado");
    printf("\nAltura: %d ", height(root));

    return 0;
}

// Função de inserção 1
Node *insert1(Node *root, int data)
{
    if (root == NULL)
    {
        root = malloc(sizeof(Node));
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    else
    {
        if (data < root->data)
            root->left = insert1(root->left, data);
        else
            root->right = insert1(root->right, data);
        return root;
    }
}

// Função de inserção 2
void insert2(Node **root, int data)
{
    if (*root == NULL)
    {
        *root = malloc(sizeof(Node));
        (*root)->data = data;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else
    {
        if (data < (*root)->data)
            insert2(&((*root)->left), data);
        else
            insert2(&((*root)->right), data);
    }
}

// Função de inserção 3
void insert3(Node **root, int data)
{
    Node *temp = *root;
    while (temp)
    {
        if (data < temp->data)
            root = &temp->left;
        else
            root = &temp->right;
        temp = *root;
    }
    temp = malloc(sizeof(Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    *root = temp;
}
// busca recursiva
Node *search1(Node *root, int data)
{
    if (root)
    {
        if (data == root->data)
            return root;
        else if (data < root->data)
            return search1(root->left, data);
        else
            return search1(root->right, data);
    }
    return NULL;
}

// busca iterativa
Node *search2(Node *root, int data)
{
    while (root)
    {
        if (data < root->data)
            root = root->left;
        else if (data > root->data)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

// Função para imprimir a árvore em ordem (in-order)
void printInOrder(Node *root)
{
    if (root != NULL)
    {
        printInOrder(root->left);
        printf("%d ", root->data);
        printInOrder(root->right);
    }
}

int height(Node *root)
{
    if (root == NULL)
        return -1;
    else
    {
        int left = height(root->left);
        int right = height(root->right);
        if (left > right)
            return left + 1;
        else
            return right + 1;
    }
}

Node *delete(Node *root, int data)
{
    if (root == NULL)
    {
        printf("Valor não encontrado\n");
        return NULL;
    }
    else
    {
        if (root->data == data)
        {
            if (root->left == NULL && root->right == NULL)
            {
                free(root);
                printf("elemento %d folha foi removido\n", data);
                return NULL;
            }
            else
            {
            }
        }
        else
        {
            if (data < root->data)
                root->left = delete (root->left, data);
            else
                root->right =delete(root->right ,data);
        }
    }
}