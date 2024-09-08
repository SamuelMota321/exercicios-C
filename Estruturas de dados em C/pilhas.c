#include <stdio.h>

// o ultimo a entrar é o primeiro a sair

typedef struct ElementoPilha
{
    int nome;
    struct ElementoPilha *prox;
};

void imprimir();
void push();
void pop();
 