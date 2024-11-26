#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "semantic.h"

// Função para executar o programa a partir da lista de tokens
void executeProgram(Token *tokenList, Table *symbolTable);

// Funçao para obter o valor de uma variavel da tabela de símbolos
int getValue(Table *symbolTable, char *identifier) {
    Table *current = symbolTable;
    while (current != NULL) {
        if (strcmp(current->identifier->value, identifier) == 0) {
            return atoi(current->identifier->value); // Converte para int
        }
        current = current->nextIdentifier;
    }
    printf("Erro: Variavel '%s' nao encontrada.\n", identifier);
    exit(1);
}

// Funçao para atualizar o valor de uma variavel na tabela de símbolos
void setValue(Table *symbolTable, char *identifier, int value) {
    Table *current = symbolTable;
    while (current != NULL) {
        if (strcmp(current->identifier->value, identifier) == 0) {
            char buffer[20];
            sprintf(buffer, "%d", value); // Converte int para string
            strcpy(current->identifier->value, buffer);
            return;
        }
        current = current->nextIdentifier;
    }
    printf("Erro: Variavel '%s' nao encontrada.\n", identifier);
    exit(1);
}

// Funçao para interpretar as instruções do programa
void executeProgram(Token *tokenList, Table *symbolTable) {
    Token *currentToken = tokenList;

    while (currentToken != NULL) {
        if (currentToken->type == IDENTIFIER && currentToken->next != NULL &&
            currentToken->next->type == OP_ASS) {
            // Atribuiçao: x := 10;
            char *identifier = currentToken->value;
            Token *expression = currentToken->next->next;

            if (expression->type == NUM_INT) {
                int value = atoi(expression->value);
                setValue(symbolTable, identifier, value);
            } else if (expression->type == IDENTIFIER) {
                int value = getValue(symbolTable, expression->value);
                setValue(symbolTable, identifier, value);
            }
        } else if (strcmp(currentToken->value, "writeln") == 0 &&
                   currentToken->next != NULL && currentToken->next->type == KEYWORD) {
            // Comando writeln: writeln(y);
            Token *expression = currentToken->next->next;
            if (expression->type == IDENTIFIER) {
                int value = getValue(symbolTable, expression->value);
                printf("%d\n", value);
            } else if (expression->type == NUM_INT) {
                printf("%s\n", expression->value);
            }
        }

        currentToken = currentToken->next;
    }
}
#endif
