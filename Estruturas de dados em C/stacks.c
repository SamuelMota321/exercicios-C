#include <stdio.h>

// o ultimo a entrar é o primeiro a sair
// possui complexidade O(n) para acesso e pesquisa,
// complexidade O(1) inserção e remoção e
// o(n) para armazenamento

typedef struct Pilha
{
    int nome;
    struct Pilha *prox;
} celula;

void imprimir();
void push(int);
void pop();

celula *top = NULL;

int main(void)
{
    int n, opcao;

    do
    {
        printf("\n\nStack Menu\n 1. Empilhar \n 2.Desempilhar \n 3.Imprimir\n 0. Sair.");
        printf("\n Escolha uma opção: 0-3: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("\nEntre com o valor que sera empilhado");
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
}
