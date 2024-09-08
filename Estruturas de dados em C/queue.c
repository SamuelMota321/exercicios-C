#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// o primeiro a entrar é o primeiro a sair (FIFO)
//  possui complexidade O(n) para acesso e pesquisa,
//  complexidade O(1) inserção e remoção e
//  O(n) para armazenamento

void imprimir();
void enqueue(int item);
void dequeue();
bool isEmpty();
bool isFull();
int getNext(int index);

int head = 0;
int tail = 0;
int queueSize = 10;
int queue[10] = {0};

int main(void)
{
    int n, opcao;

    do
    {
        printf("\n\nQueue Menu\n 1. Enfileirar \n 2.Desenfileirar \n 3.Imprimir\n 0. Sair.");
        printf("\n Escolha uma opcaoo: 0-3: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("\nEntre com o valor que sera enfileirado: ");
            scanf("%d", &n);
            enqueue(n);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            imprimir();
            break;
        }
    } while (opcao != 0);

    return 0;
}

int getNext(int index)
{
    if (index == queueSize - 1)
    {
        return 0;
    }
    else
    {
        return index + 1;
    }
}

bool isEmpty()
{
    if (head == tail && queue[0] == 0)
    {
        return true;
    }
    return false;
}

bool isFull()
{
    if ((getNext(tail) == head) || ((head == 0) && (tail == queueSize - 1)))
    {
        return true;
    }
    return false;
}

void enqueue(int item)
{
    printf("\n==========================");
    printf("\n=======Enfileirando=======");
    if (isFull())
    {
        printf("\nA fila esta cheia, aguarde\n");
    }
    else
    {
        if (!isEmpty())
        {
            tail = getNext(tail);
        }
        queue[tail] = item;
        printf("\nValor %d enfileirado", queue[tail]);
    }
}

void dequeue()
{
    printf("\n=============================");
    printf("\n=======Desenfileirando=======");
    if (isEmpty())
    {
        printf("\nA fila esta vazia\n");
    }
    else
    {

        printf("\n\n%d desenfileirando", queue[head]);
        queue[head] = 0;
        head = getNext(head);
    }
}

void imprimir()
{
    int temp = head;
    printf("\n=============================");
    printf("\n=======Imprimindo fila=======\n");
    if (isEmpty())
    {
        printf("\n A fila esta vazia");
    }
    else
    {
        do
        {
            printf("%d ", queue[temp]);
            temp = getNext(temp);
        } while (temp != getNext(tail));
    }
}