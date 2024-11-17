#ifndef SYNTACTIC_H
#define SYNTACTIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"

// Funções principais para o analisador sintático
void parseProgram(Token **current);
void parseBlock(Token **current);
void parseVariableDeclarations(Token **current);
void parseVariableDeclaration(Token **current);
void parseCommandCompound(Token **current);
void parseCommand(Token **current);
void parseAssignment(Token **current);
void parseConditional(Token **current);
void parseRepetitive(Token **current);
void parseExpression(Token **current);
void parseSimpleExpression(Token **current);
void parseTerm(Token **current);
void parseFactor(Token **current);
void parseVariable(Token **current);

void syntaxError(const char *message, Token *current)
{
    printf("Erro de sintaxe: %s. Token atual: %s\n", message, current->value);
    exit(1);
}

// Função auxiliar para verificar um token específico e avançar
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

// Função principal para iniciar o parsing
void parseProgram(Token **current)
{
    // <programa> ::= program <identificador> ; <bloco> .
    if ((*current)->type == KEYWORD && strcmp((*current)->value, "program") == 0)
    {
        *current = (*current)->next;
        expect(current, IDENTIFIER); // Espera um identificador
        expect(current, SMB_SEM);    // Espera ';'
        parseBlock(current);         // Chama o parsing do bloco principal
        expect(current, SMB_PTO);    // Espera '.'
    }
    else
    {
        syntaxError("Esperado 'program' no início do programa", *current);
    }
}

void parseBlock(Token **current)
{
    // <bloco> ::= <parte de declarações de variáveis> <comando composto>
    parseVariableDeclarations(current);
    parseCommandCompound(current);
}

void parseVariableDeclarations(Token **current)
{
    // <parte de declarações de variáveis> ::= ( var <declaração de variáveis> (; <declaração de variáveis>)* ; )*
    while ((*current)->type == KEYWORD && strcmp((*current)->value, "var") == 0)
    {
        *current = (*current)->next;
        parseVariableDeclaration(current);
        expect(current, SMB_SEM);
    }
}

void parseVariableDeclaration(Token **current)
{
    // <declaração de variáveis> ::= <lista de identificadores> : <tipo>
    while ((*current)->type == IDENTIFIER)
    {
        *current = (*current)->next;
        if ((*current)->type == SMB_COM)
        {
            *current = (*current)->next; // Avança após ','
        }
    }
    expect(current, SMB_COL); // Espera ':'

    // Espera um tipo: integer, real ou boolean
    if ((*current)->type == KEYWORD &&
        (strcmp((*current)->value, "integer") == 0 ||
         strcmp((*current)->value, "real") == 0 ||
         strcmp((*current)->value, "boolean") == 0))
    {
        *current = (*current)->next;
    }
    else
    {
        syntaxError("Esperado um tipo (integer, real, boolean)", *current);
    }
}

void parseCommandCompound(Token **current)
{
    // <comando composto> ::= begin <comando> { ; <comando> } end
    if ((*current)->type == KEYWORD && strcmp((*current)->value, "begin") == 0)
    {
        *current = (*current)->next; // Avança após "begin"
        parseCommand(current); // Processa o primeiro comando

        while ((*current)->type == SMB_SEM) // Consome comandos separados por ";"
        {
            *current = (*current)->next; // Avança após ";"
            parseCommand(current); // Processa o próximo comando
        }

        if ((*current)->type == KEYWORD && strcmp((*current)->value, "end") == 0)
        {
            *current = (*current)->next; // Avança após "end"
        }
        else
        {
            syntaxError("Esperado 'end' para fechar o bloco de comandos", *current);
        }
    }
    else
    {
        syntaxError("Esperado 'begin' para iniciar o bloco de comandos", *current);
    }
}


void parseWriteln(Token **current)
{
    *current = (*current)->next; // Avança após "writeln"
    printf("%s", (*current)->value);

    // Verifica e consome o token de abertura de parêntese "("
    expect(current, SMB_OPA); // Função que gera erro se o próximo token não for "("

    // Processa os argumentos dentro do parêntese
    while ((*current)->type != SMB_CPA)
    { // Enquanto não encontra ")"
        if ((*current)->type == STRING)
        {
            // Se for uma string literal, avançamos
            *current = (*current)->next;
        }
        else if ((*current)->type == IDENTIFIER)
        {
            // Se for um identificador (como uma variável), avançamos
            *current = (*current)->next;
        }
        else
        {
            syntaxError("Esperado uma string ou identificador", *current);
        }

        // Verifica se há uma vírgula antes do próximo argumento
        if ((*current)->type == SMB_COM)
        {
            *current = (*current)->next; // Consome a vírgula
        }
        else if ((*current)->type != SMB_CPA)
        {
            // Se não há vírgula e o próximo não é ")", é um erro de sintaxe
            syntaxError("Esperado ',' ou ')'", *current);
        }
    }

    // Consome o parêntese de fechamento
    expect(current, SMB_CPA);
    // Espera o ponto e vírgula no final da chamada
    expect(current, SMB_SEM);
}

void parseCommand(Token **current)
{

    // <comado> ::= <atribuição> | <comando composto> | <comando condicional> | <comando repetitivo>
    if ((*current)->type == IDENTIFIER)
    {
        parseAssignment(current); // Atribuição
    }
    else if ((*current)->type == KEYWORD && strcmp((*current)->value, "if") == 0)
    {
        parseConditional(current); // Comando condicional
    }
    else if ((*current)->type == KEYWORD && strcmp((*current)->value, "while") == 0)
    {
        parseRepetitive(current); // Comando repetitivo
    }
    else if ((*current)->type == KEYWORD && strcmp((*current)->value, "begin") == 0)
    {
        parseCommandCompound(current); // Bloco de comandos
    }
    else if ((*current)->type == KEYWORD && strcmp((*current)->value, "end") == 0)
    {
        printf("end of file");
    }
    else
    {
        syntaxError("Comando inesperado", *current);
    }
}

void parseAssignment(Token **current)
{
    if ((*current)->type == IDENTIFIER && strcmp((*current)->value, "writeln") == 0)
    {
        parseWriteln(current);
    }
    // <atribuição> ::= <variável> := <expressão>
    parseVariable(current);
    expect(current, OP_ASS); // Espera ':='
    parseExpression(current);
}

void parseConditional(Token **current)
{
    // <comando condicional> ::= if <expressão> then <comando> [ else <comando> ]
    *current = (*current)->next; // Avança após "if"
    parseExpression(current); // Processa a expressão condicional
    if ((*current)->type == KEYWORD && strcmp((*current)->value, "then") == 0)
    {
        *current = (*current)->next; // Avança após "then"
        parseCommand(current); // Processa o comando após "then"

        if ((*current)->type == KEYWORD && strcmp((*current)->value, "else") == 0)
        {
            *current = (*current)->next; // Avança após "else"
            parseCommand(current); // Processa o comando após "else"
        }
    }
    else
    {
        syntaxError("Esperado 'then' após a expressão condicional", *current);
    }
}


void parseRepetitive(Token **current)
{
    // <comando repetitivo> ::= while <expressão> do <comando>
    *current = (*current)->next; // Avança após "while"
    parseExpression(current);
    expect(current, KEYWORD); // Espera "do"
    parseCommand(current);
}

void parseExpression(Token **current)
{
    // <expressão> ::= <expressão simples> [ <relação> <expressão simples> ]
    parseSimpleExpression(current);
    if ((*current)->type == OP_EQ || (*current)->type == OP_NE ||
        (*current)->type == OP_LT || (*current)->type == OP_LE ||
        (*current)->type == OP_GE || (*current)->type == OP_GT)
    {
        *current = (*current)->next; // Avança após operador relacional
        parseSimpleExpression(current);
    }

    if ((*current)->type == SMB_OPA)
    {
        *current = (*current)->next;
        parseExpression(current); // Processa a subexpressão dentro do parêntese
        expect(current, SMB_CPA); // Espera o fechamento do parêntese
    }
}

void parseSimpleExpression(Token **current)
{
    // <expressão simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
    if ((*current)->type == OP_AD || (*current)->type == OP_MIN)
    {
        *current = (*current)->next;
    }
    parseTerm(current);
    while ((*current)->type == OP_AD || (*current)->type == OP_MIN)
    {
        *current = (*current)->next;
        parseTerm(current);
    }
}

void parseTerm(Token **current)
{
    // <termo> ::= <fator> { ( * | / ) <fator> }
    parseFactor(current);
    while ((*current)->type == OP_MUL || (*current)->type == OP_DIV)
    {
        *current = (*current)->next;
        parseFactor(current);
    }
}

void parseFactor(Token **current)
{
    // <fator> ::= <variável> | <número> | ( <expressão> )
    if ((*current)->type == IDENTIFIER)
    {
        parseVariable(current);
    }
    else if ((*current)->type == NUM_INT || (*current)->type == NUM_FLT)
    {
        *current = (*current)->next;
    }
    else if ((*current)->type == SMB_OPA)
    {
        *current = (*current)->next;
        parseExpression(current);
        expect(current, SMB_CPA);
    }
    else
    {
        syntaxError("Esperado um fator", *current);
    }
}

void parseVariable(Token **current)
{
    // <variável> ::= <identificador>
    expect(current, IDENTIFIER);
}

#endif
