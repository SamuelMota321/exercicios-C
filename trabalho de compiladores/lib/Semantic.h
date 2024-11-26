#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokens.h"

// Função para obter o tipo associado a um token
char *getTypeFromToken(Table *symbolTable, Token *token)
{
    if (token == NULL || symbolTable == NULL)
        return NULL;

    // Se for um identificador, procure na tabela de símbolos
    if (token->type == IDENTIFIER)
    {
        Table *current = symbolTable;
        while (current != NULL)
        {
            if (strcmp(current->identifier->value, token->value) == 0)
            {
                // Retorna o tipo associado como string
                if (current->identifier->type == NUM_INT) return "integer";
                if (current->identifier->type == NUM_FLT) return "real";
                if (current->identifier->type == STRING) return "string";
                return "unknown"; // Tipo desconhecido, por segurança
            }
            current = current->nextIdentifier;
        }
        printf("Erro semântico: Identificador '%s' não declarado.\n", token->value);
        return NULL;
    }

    // Se for um valor constante, determine o tipo
    if (token->type == NUM_INT)
        return "integer";
    if (token->type == NUM_FLT)
        return "real";
    if (token->type == STRING)
        return "string";

    return NULL; // Para outros casos, tipo indefinido
}

// Função para verificar se um identificador foi declarado
int isDeclared(Table *symbolTable, char *identifier)
{
    if (symbolTable == NULL || identifier == NULL)
        return 0;

    Table *current = symbolTable;
    while (current != NULL)
    {
        if (strcmp(current->identifier->value, identifier) == 0)
            return 1;
        current = current->nextIdentifier;
    }
    return 0;
}

// Função para atualizar o valor de uma variável na tabela de símbolos
void updateVariableValue(Table *symbolTable, Token *identifier, int value)
{
    if (symbolTable == NULL || identifier == NULL)
        return;

    Table *current = symbolTable;
    while (current != NULL)
    {
        if (strcmp(current->identifier->value, identifier->value) == 0)
        {
            current->value = value; // Atualiza o valor da variável
            return;
        }
        current = current->nextIdentifier;
    }
}

// Função para verificar compatibilidade de tipos
int isCompatibleType(Table *symbolTable, Token *left, Token *right)
{
    if (symbolTable == NULL || left == NULL || right == NULL)
        return 0;

    // Obter tipos associados aos tokens
    char *leftType = getTypeFromToken(symbolTable, left);
    char *rightType = getTypeFromToken(symbolTable, right);

    if (leftType == NULL || rightType == NULL)
    {
        printf("Erro semântico: Tipo indefinido para a expressão.\n");
        return 0;
    }

    // Verificar compatibilidade básica
    if (strcmp(leftType, rightType) == 0)
        return 1; // Tipos são compatíveis

    // Regras adicionais para conversões implícitas
    if ((strcmp(leftType, "real") == 0 && strcmp(rightType, "integer") == 0) ||
        (strcmp(leftType, "integer") == 0 && strcmp(rightType, "real") == 0))
    {
        return 1; // Permitimos conversão entre integer e real
    }

    printf("Erro semântico: Tipos incompatíveis ('%s' e '%s') na linha %d, coluna %d.\n",
           leftType, rightType, left->line, left->colunm);
    return 0;
}

// Função principal para análise semântica
void analyzeSemantic(Token *tokenList, Table *symbolTable)
{
    if (symbolTable == NULL || tokenList == NULL)
        return;

    Token *currentToken = tokenList;

    while (currentToken != NULL)
    {
        switch (currentToken->type)
        {
        case IDENTIFIER:
            if (!isDeclared(symbolTable, currentToken->value))
            {
                printf("Erro semântico: Identificador '%s' na linha %d, coluna %d não declarado.\n",
                       currentToken->value, currentToken->line, currentToken->colunm);
            }
            break;
        case OP_ASS:
            if (!isCompatibleType(symbolTable, currentToken->previous, currentToken->next))
            {
                printf("Erro semântico: Incompatibilidade de tipos na linha %d, coluna %d.\n",
                       currentToken->line, currentToken->colunm);
            }
            else
            {
                // Converte o valor da expressão para inteiro antes de atualizar
                int value = atoi(currentToken->next->value); // Converte string para inteiro
                updateVariableValue(symbolTable, currentToken->previous, value);
            }
            break;
        default:
            break;
        }

        currentToken = currentToken->next;
    }
}

#endif
