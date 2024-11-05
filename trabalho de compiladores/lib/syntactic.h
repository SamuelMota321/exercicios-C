#ifndef SYNTACTIC_H
#define SYNTACTIC_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"
#include <string.h>



// Função para imprimir erros de sintaxe com detalhes do token atual
void syntaxError(const char *message, Token *current) {
    printf("Erro de sintaxe: %s. Token atual: %s\n", message, current->value);
    exit(EXIT_FAILURE);
}

// Função que espera um token específico e avança
void expect(Token **current, TokenType expectedType) {
    if ((*current)->type == expectedType) {
        *current = (*current)->next;
    } else {
        syntaxError("Token inesperado", *current);
    }
}

// Função para verificar e interpretar uma expressão (números, identificadores, ou expressões aritméticas)
void parseExpression(Token **current) {
    if ((*current)->type == NUM_INT || (*current)->type == IDENTIFIER) {
        *current = (*current)->next;
        if ((*current)->type == OP_AD || (*current)->type == OP_MIN || 
            (*current)->type == OP_MUL || (*current)->type == OP_DIV) {
            *current = (*current)->next;
            parseExpression(current);
        }
    } else {
        syntaxError("Esperado um número ou identificador", *current);
    }
}

// Função para interpretar uma atribuição, como `x := 10;`
void parseAssignment(Token **current) {
    if ((*current)->type == IDENTIFIER) {
        *current = (*current)->next;       // Avança para o próximo token
        expect(current, OP_ASS);           // Espera operador de atribuição :=
        parseExpression(current);          // Interpreta a expressão à direita
        expect(current, SMB_SEM);          // Espera ponto e vírgula
    } else {
        syntaxError("Esperado um identificador para a atribuição", *current);
    }
}

// Função para interpretar a chamada `writeln`
void parseWriteln(Token **current) {
    if (strcmp((*current)->value, "writeln") == 0) { // Verifica se é "writeln"
        *current = (*current)->next;              // Avança
        expect(current, SMB_OPA);                 // Espera parênteses de abertura (
        parseExpression(current);                 // Interpreta a expressão dentro de writeln
        expect(current, SMB_CPA);                 // Espera parênteses de fechamento )
        expect(current, SMB_SEM);                 // Espera ponto e vírgula ;
    } else {
        syntaxError("Esperado 'writeln'", *current);
    }
}

// Função para interpretar blocos de código `begin ... end`
void parseBlock(Token **current) {
    if (strcmp((*current)->value, "begin") == 0) { // Verifica se é "begin"
        *current = (*current)->next;               // Avança para o próximo token

        // Interpreta cada instrução até encontrar `end`
        while (strcmp((*current)->value, "end") != 0) {
            if ((*current)->type == IDENTIFIER) {
                parseAssignment(current);           // Atribuição
            } else if (strcmp((*current)->value, "writeln") == 0) {
                parseWriteln(current);              // Chamada de função writeln
            } else {
                syntaxError("Instrução inválida no bloco", *current);
            }
        }

        *current = (*current)->next;               // Avança para o próximo token após "end"
        expect(current, SMB_PTO);                  // Espera o ponto final (.)
    } else {
        syntaxError("Esperado 'begin' para iniciar o bloco", *current);
    }
}

// Função principal do analisador sintático
void syntactic(Token *initialToken) {
    Token *current = initialToken;
    parseBlock(&current);                          // Inicia a interpretação do bloco principal
    if (current->type == END_OF_FILE) {
        printf("Análise sintática concluída com sucesso.\n");
    } else {
        syntaxError("Esperado final de arquivo", current);
    }
}


#endif
