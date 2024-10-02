#include <stdio.h>

#include <stdio.h>

// Definição da estrutura da árvore binária de busca
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
void printInOrder(Node *root);
Node *rightRotation(Node *root);
short height(Node *node);
short big(short left, short right);
short balancingFactor(Node *node);

int main(void)
{
    Node *root = NULL;
    Node *search = NULL;
    insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 55);
    insert(root, 60);
    insert(root, 80);
    insert(root, 90);
    root = delete (root, 60);
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
        printf("\n Erro ao alocar memoria para um novo no");
}

Node *insert(Node *root, int data)
{
    if (root == NULL)
        return createNode(data);
    else
    {
        if (data < root->data)
            root->left = insert(root->left, data);
        else if (data > root->data)
            root->right = insert(root->right, data);
        else
            printf("\nInsecao nao realizada!\n o elemento %d ja existe\n", data);
    }

    root->height = big(height(root->left), height(root->right) + 1);
    root = balancing(root);
    return root;
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

Node *balancing(Node *root)
{
    short fb = balancingFactor(root);

    if (fb < -1 && balancingFactor(root->right) <= 0)
        root = leftRotation(root);
    else if (fb > 1 && balancingFactor(root->left) >= 0)
        root = rightRotation(root);
    else if (fb > 1 && balancingFactor(root->left) < 0)
        root = leftRightRotation(root);
    else if (fb < -1 && balancingFactor(root->right) > 0)
        root = rightLeftRotation;

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
    Node *newRoot, *f;
    newRoot = root->left;
    f = newRoot->right;

    newRoot->right = root;
    root->left = f;

    root->height = big(height(root->left), height(root->right)) + 1;
    newRoot->height = big(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}
Node *leftRotation(Node *root)
{
    Node *newRoot, *f;
    newRoot = root->right;
    f = newRoot->left;

    newRoot->left = root;
    root->right = f;

    root->height = big(height(root->left), height(root->right)) + 1;
    newRoot->height = big(height(newRoot->left), height(newRoot->right)) + 1;

    return newRoot;
}

short balancingFactor(Node *node)
{
    if (node)
        return (height(node->left) - height(node->right));
    else
        return 0;
}

short big(short left, short right)
{
    return (left > right) ? left : right;
}

short height(Node *node)
{
    if (node == NULL)
        return -1;
    else
        return node->height;
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
                    root->left = delete (root->left, data);
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
        
        root->height = big(height(root->left), height(root->right) + 1);
        root = balancing(root);
        return root;
    }
}