#include <stdio.h>
#include <stdlib.h>

// o ultimo a entrar é o primeiro a sair (LIFO)
// possui complexidade O(n) para acesso e pesquisa,
// complexidade O(1) inserção e remoção e
// O(n) para armazenamento

typedef struct Pilha
{
    int dado;
    struct Pilha *prox;
} celula;

celula *top = NULL;

void push(int);
void pop();
void imprimir();

int main(void)
{
    int n, opcao;

    do
    {
        printf("\n\nStack Menu\n 1. Empilhar \n 2.Desempilhar \n 3.Imprimir\n 0. Sair.");
        printf("\n Escolha uma opcaoo: 0-3: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("\nEntre com o valor que sera empilhado: ");
            scanf("%d", &n);
            push(n);
            break;
        case 2:
            pop();
            break;
        case 3:
            imprimir();
            break;
        }
    } while (opcao != 0);

    return 0;
}

void push(int item)
{
    printf("========================");
    printf("\n=======Empilhando=======");
    celula *novo = malloc(sizeof(celula));
    novo->dado = item;
    novo->prox = top;
    top = novo;
    printf("\nValor %d empilhado\n", novo->dado);
    printf("========================");
};

void pop()
{
    printf("\n======================");
    printf("\n====Desempilhando=====\n");
    if (top == NULL)
    {
        printf("A pilha esta vazia");
    }
    else
    {
        celula *temp = top;
        top = top->prox;
        printf("\n\n %d desempilhado", temp->dado);
        free(temp);
    }
}

void imprimir()
{
    celula *temp = top;
    printf("\n======================");
    printf("\n======Imprimindo======");
    if (temp != NULL)
    {

        while (temp != NULL)
        {
            printf("\n%d", temp->dado);
            temp = temp->prox;
        }
    }
    else
    {
        printf("\n==A pilha esta vazia==");
    }
    free(temp);
}