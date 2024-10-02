#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da árvore AVL
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    short height;
} Node;

Node *insert(Node *root, int data);
Node *search(Node *root, int data);
Node *delete(Node *root, int data);
Node *createNode(int data);
Node *leftRotation(Node *root);
void printInOrder(Node *root, int level);
Node *rightRotation(Node *root);
short height(Node *node);
short max(short left, short right);
Node *balancing(Node *root);
Node *leftRightRotation(Node *root);
Node *rightLeftRotation(Node *root);
short balancingFactor(Node *node);

int main(void)
{
    Node *root = NULL;
    Node *searchResult = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 55);
    root = insert(root, 60);
    root = insert(root, 80);
    root = insert(root, 90);

    root = delete (root, 60);

    printf("Raiz: %d Arvore em ordem:  ", root->data);
    printInOrder(root, 0);
    printf("\n");

    searchResult = search(root, 80);
    if (searchResult)
        printf("Valor encontrado na busca: %d\n", searchResult->data);
    else
        printf("Valor não encontrado\n");

    printf("Altura da árvore: %d\n", height(root));

    return 0;
}

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode)
    {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 0;
    }
    else
    {
        printf("\nErro ao alocar memória para um novo nó\n");
    }
    return newNode;
}

Node *insert(Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert(root->right, data);
    }
    else
    {
        printf("\nInserção não realizada! O elemento %d já existe.\n", data);
        return root;
    }

    // Atualizar a altura
    root->height = 1 + max(height(root->left), height(root->right));

    // Balancear a árvore
    return balancing(root);
}

Node *search(Node *root, int data)
{
    while (root != NULL)
    {
        if (data < root->data)
        {
            root = root->left;
        }
        else if (data > root->data)
        {
            root = root->right;
        }
        else
        {
            return root;
        }
    }
    return NULL;
}

void printInOrder(Node *root, int level)
{
    if (root)
    {
        printInOrder(root->right, level + 1);
        printf("\n");

        for (int i = 0; i < level; i++)
        {
            printf("\t");
        }

        printf("%d", root->data);
        printInOrder(root->left, level + 1);
    }
}

Node *balancing(Node *root)
{
    short bf = balancingFactor(root);

    // Rotação esquerda
    if (bf < -1 && balancingFactor(root->right) <= 0)
    {
        return leftRotation(root);
    }

    // Rotação direita
    if (bf > 1 && balancingFactor(root->left) >= 0)
    {
        return rightRotation(root);
    }

    // Rotação dupla direita-esquerda
    if (bf > 1 && balancingFactor(root->left) < 0)
    {
        return leftRightRotation(root);
    }

    // Rotação dupla esquerda-direita
    if (bf < -1 && balancingFactor(root->right) > 0)
    {
        return rightLeftRotation(root);
    }

    return root;
}

Node *rightLeftRotation(Node *root)
{
    root->right = rightRotation(root->right);
    return leftRotation(root);
}

Node *leftRightRotation(Node *root)
{
    root->left = leftRotation(root->left);
    return rightRotation(root);
}

Node *rightRotation(Node *root)
{
    Node *newRoot = root->left;
    Node *temp = newRoot->right;

    newRoot->right = root;
    root->left = temp;

    // Atualizar alturas
    root->height = 1 + max(height(root->left), height(root->right));
    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

Node *leftRotation(Node *root)
{
    Node *newRoot = root->right;
    Node *temp = newRoot->left;

    newRoot->left = root;
    root->right = temp;

    // Atualizar alturas
    root->height = 1 + max(height(root->left), height(root->right));
    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

short balancingFactor(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

short max(short left, short right)
{
    return (left > right) ? left : right;
}

short height(Node *node)
{
    if (node == NULL)
    {
        return -1;
    }
    return node->height;
}

Node *delete(Node *root, int data)
{
    if (root == NULL)
    {
        printf("Valor não encontrado\n");
        return NULL;
    }

    if (data < root->data)
    {
        root->left = delete (root->left, data);
    }
    else if (data > root->data)
    {
        root->right = delete (root->right, data);
    }
    else
    {
        // Nó encontrado
        if (root->left == NULL || root->right == NULL)
        {
            Node *temp = (root->left) ? root->left : root->right;
            free(root);
            return temp;
        }
        else
        {
            Node *temp = root->left;
            while (temp->right != NULL)
            {
                temp = temp->right;
            }
            root->data = temp->data;
            root->left = delete (root->left, temp->data);
        }
    }

    // Atualizar a altura
    root->height = 1 + max(height(root->left), height(root->right));

    // Balancear a árvore
    root = balancing(root);
    return root;
}
