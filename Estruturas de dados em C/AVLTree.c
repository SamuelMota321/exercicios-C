#include <stdio.h>


#include <stdio.h>

// Definição da estrutura da árvore binária de busca
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

void insert(Node **root, int data);
Node *search(Node *root, int data);
Node *delete(Node *root, int data);
void printInOrder(Node *root);
int height(Node *root);

int main(void)
{
    Node *root = NULL;
    Node *search = NULL;
    insert(&root, 50);
    insert(&root, 30);
    insert(&root, 70);
    insert(&root, 20);
    insert(&root, 40);
    insert(&root, 55);
    insert(&root, 60);
    insert(&root, 80);
    insert(&root, 90);
    root = delete(root, 60);
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


void insert(Node **root, int data)
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

Node *search(Node *root, int data)
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
                if (root->left != NULL && root->right != NULL)
                {
                    Node *temp = root->left;
                    while (temp->right != NULL)
                        temp = temp->right;
                        root->data = temp->data;
                        temp->data = data;
                        root->left = delete(root->left, data);

                }
                else
                {
                    Node *temp;
                    if (root->left != NULL)
                    {
                        temp = root->left;
                    }
                    else
                        temp = root->right;
                    free(root);
                    return temp; 
                }
            }
        }
        else
        {
            if (data < root->data)
                root->left = delete (root->left, data);
            else
                root->right = delete (root->right, data);
        }
    }
}