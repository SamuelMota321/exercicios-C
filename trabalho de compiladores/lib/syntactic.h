#ifndef SYNTACTIC_H
#define SYNTACTIC_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokens.h"
#include <string.h>

// Função para imprimir erros de sintaxe com detalhes do token atual
void syntaxError(const char *message, Token *current)
{
    printf("Erro de sintaxe: %s. Token atual: %s\n", message, current->value);
    exit(EXIT_FAILURE);
}

// Função que espera um token específico e avança
void expect(Token **current, TokenType expectedType)
{
    if ((*current)->type == expectedType)
    {
        *current = (*current)->next;
    }
    else
    {
        syntaxError("Token inesperado", *current);
    }
}

// Função para verificar e interpretar uma expressão (números, identificadores, ou expressões aritméticas)
void parseExpression(Token **current)
{
    // Verifica se a expressão inicia com um número, identificador ou parêntese aberto
    if ((*current)->type == NUM_INT || (*current)->type == NUM_FLT || (*current)->type == IDENTIFIER)
    {
        *current = (*current)->next; // Avança para o próximo token
    }
    else if ((*current)->type == SMB_OPA)
    {                                // Verifica parênteses de abertura '('
        *current = (*current)->next; // Avança após '('
        parseExpression(current);    // Avalia a expressão dentro dos parênteses
        if ((*current)->type == SMB_CPA)
        {                                // Verifica parênteses de fechamento ')'
            *current = (*current)->next; // Avança após ')'
        }
        else
        {
            syntaxError("Esperado ')'", *current);
        }
    }
    else
    {
        syntaxError("Esperado um numero, identificador ou ' ('", *current);
    }

    // Verifica se a expressão continua com operadores aritméticos
    while ((*current)->type == OP_AD || (*current)->type == OP_MIN ||
           (*current)->type == OP_MUL || (*current)->type == OP_DIV)
    {
        *current = (*current)->next; // Avança após o operador
        if ((*current)->type == NUM_INT || (*current)->type == NUM_FLT || (*current)->type == IDENTIFIER)
        {
            *current = (*current)->next; // Avança após o operando
        }
        else if ((*current)->type == SMB_OPA)
        {                                // Permite sub-expressão com '('
            *current = (*current)->next; // Avança após '('
            parseExpression(current);    // Avalia a sub-expressão
            if ((*current)->type == SMB_CPA)
            { // Verifica ')'
                *current = (*current)->next;
            }
            else
            {
                syntaxError("Esperado ')'", *current);
            }
        }
        else
        {
            syntaxError("Esperado um numero, identificador ou sub-expressao apos o operador", *current);
        }
    }
}

// Função para interpretar uma atribuição, como `x := 10;`
void parseAssignment(Token **current)
{
    if ((*current)->type == IDENTIFIER)
    {
        *current = (*current)->next; // Avança para o próximo token
        expect(current, OP_ASS);     // Espera operador de atribuição :=
        parseExpression(current);    // Interpreta a expressão à direita
        expect(current, SMB_SEM);    // Espera ponto e vírgula
    }
    else
    {
        syntaxError("Esperado um identificador para a atribuicao", *current);
    }
}

// Função para interpretar a chamada `writeln`
void parseWriteln(Token **current)
{
    if ((*current)->type == KEYWORD && strcmp((*current)->value, "writeln") == 0)
    {
        *current = (*current)->next; // Avança
        expect(current, SMB_OPA);    // Espera parênteses de abertura (
        parseExpression(current);    // Interpreta a expressão dentro de writeln
        expect(current, SMB_CPA);    // Espera parênteses de fechamento )
        expect(current, SMB_SEM);    // Espera ponto e vírgula ;
    }
    else
    {
        syntaxError("Esperado 'writeln'", *current);
    }
}

void parseBlock(Token **current);

void parseIfStatement(Token **current) {
    if ((*current)->type == KEYWORD && strcmp((*current)->value, "if") == 0) {
        *current = (*current)->next;  // Avança para o próximo token após "if"
        
        parseExpression(current);  // Verifica a condição após o "if"
        
        // Espera o token "then" após a condição
        if (!((*current)->type == KEYWORD && strcmp((*current)->value, "then") == 0)) {
            syntaxError("Esperado 'then' após a condição 'if'", *current);
            return;
        }
        
        *current = (*current)->next;  // Avança para o próximo token após "then"
        
        // Processa o bloco do "then" (pode ser uma única instrução ou um bloco "begin-end")
        if ((*current)->type == KEYWORD && strcmp((*current)->value, "begin") == 0) {
            parseBlock(current);  // Chama parseBlock para processar um bloco begin-end
        } else {
            parseIfStatement(current);  // Processa uma única instrução
        }

        // Verifica se existe um "else" opcional
        if ((*current)->type == KEYWORD && strcmp((*current)->value, "else") == 0) {
            *current = (*current)->next;  // Avança para o próximo token após "else"
            
            // Processa o bloco do "else" (pode ser uma única instrução ou um bloco "begin-end")
            if ((*current)->type == KEYWORD && strcmp((*current)->value, "begin") == 0) {
                parseBlock(current);  // Chama parseBlock para processar um bloco begin-end
            } else {
                parseIfStatement(current);  // Processa uma única instrução
            }
        }
    } else {
        syntaxError("Esperado 'if' no início da condição", *current);
    }
}


void parseBlock(Token **current) {
    if ((*current)->type == KEYWORD && strcmp((*current)->value, "begin") == 0) {
        *current = (*current)->next;  // Avança para o próximo token

        // Interpreta cada instrução até encontrar `end`
        while (!((*current)->type == KEYWORD && strcmp((*current)->value, "end") == 0)) {
            if ((*current)->type == IDENTIFIER) {
                parseAssignment(current);  // Atribuição
            } else if ((*current)->type == KEYWORD && strcmp((*current)->value, "writeln") == 0) {
                parseWriteln(current);     // Chamada de função writeln
            } else if ((*current)->type == KEYWORD && strcmp((*current)->value, "if") == 0) {
                parseIfStatement(current); // Instrução condicional if-then-else
            } else {
                syntaxError("Instrução inválida no bloco", *current);
            }
        }

        *current = (*current)->next;  // Avança para o próximo token após "end"
        expect(current, SMB_PTO);     // Espera o ponto final (.)
    } else {
        syntaxError("Esperado 'begin' para iniciar o bloco", *current);
    }
}


// Função principal do analisador sintático
void syntactic(Token *initialToken)
{
    Token *current = initialToken;
    parseBlock(&current); // Inicia a interpretação do bloco principal
    if (current->type == END_OF_FILE)
    {
        printf("Análise sintática concluída com sucesso.\n");
    }
    else
    {
        syntaxError("Esperado final de arquivo", current);
    }
}

#endif
