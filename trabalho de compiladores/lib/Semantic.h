#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h> // Adicionada para reconhecer INT_MIN e INT_MAX
#include "tokens.h"

// Função para imprimir erros semânticos com detalhes
void printSemanticError(const char *message, Token *token) {
    if (token != NULL) {
        printf("Erro semântico: %s na linha %d, coluna %d.\n", 
               message, token->line, token->colunm);
    } else {
        printf("Erro semântico: %s\n", message);
    }
}

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
                if (current->identifier->type == NUM_INT)
                    return "integer";
                if (current->identifier->type == NUM_FLT)
                    return "real";
                if (current->identifier->type == STRING)
                    return "string";
                return "unknown"; // Tipo desconhecido, por segurança
            }
            current = current->nextIdentifier;
        }
        printSemanticError("Identificador não declarado", token);
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
            // Atualiza o valor da variável (caso seja um tipo numérico)
            if (current->identifier->type == NUM_INT)
            {
                current->value = value; // Atualiza o valor inteiro
            }
            else
            {
                printSemanticError("Tipo incompatível para atribuição de valor à variável", identifier);
            }
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
        printSemanticError("Tipo indefinido para a expressão", left);
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

    printSemanticError("Tipos incompatíveis", left);
    return 0;
}

// Função para converter uma string para um inteiro de maneira segura
int safeAtoi(const char *str)
{
    char *endptr;
    long result = strtol(str, &endptr, 10);
    if (*endptr != '\0') {
        printf("Erro: '%s' não é um número válido.\n", str);
        return 0;  // Retorna 0 para indicar erro
    }
    if (result < INT_MIN || result > INT_MAX) {
        printf("Erro: '%s' está fora do intervalo de inteiros.\n", str);
        return 0;  // Retorna 0 para indicar erro
    }
    return (int)result;
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
                printSemanticError("Identificador não declarado", currentToken);
            }
            break;
        case OP_ASS:
            if (!isCompatibleType(symbolTable, currentToken->previous, currentToken->next))
            {
                printSemanticError("Incompatibilidade de tipos", currentToken);
            }
            else
            {
                // Converte o valor da expressão para inteiro antes de atualizar
                int value = safeAtoi(currentToken->next->value);
                if (value != 0) { // Se a conversão foi bem-sucedida
                    updateVariableValue(symbolTable, currentToken->previous, value);
                }
            }
            break;
        default:
            break;
        }

        currentToken = currentToken->next;
    }
}

#endif
