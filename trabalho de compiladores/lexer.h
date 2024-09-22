#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *keywords[] = {"and", "array", "begin", "case", "const", "div", "do", "downto", "else", "end", "for",
                    "function", "if", "in", "integer", "label", "mod", "not", "of", "or", "procedure", "program", "record", "repeat",
                    "set", "then", "to", "type", "var", "while", "with"};

int num_keywords = 31;

typedef enum
{
    // Operadores Aritméticos
    OP_AD,  // +
    OP_MIN, // -
    OP_MUL, // *
    OP_DIV, // /

    // Operadores de Comparação
    OP_EQ, // =
    OP_NE, // <>
    OP_GT, // >
    OP_LT, // <
    OP_GE, // >=
    OP_LE, // <=

    // Operador de tribuição
    OP_ASS, // :=

    // Delimitadores
    SMB_SEM, // ;
    SMB_COL, // :
    SMB_COM, // ,
    SMB_PTO, // . (ponto, para finalização)

    // Parênteses e Colchetes
    SMB_OPA, // ( (parênteses de abertura)
    SMB_CPA, // ) (parênteses de fechamento)
    SMB_OBC, // [ (colchete de abertura)
    SMB_CBC, // ] (colchete de fechamento)

    // Chaves
    SMB_OBR, // { (chave de abertura)
    SMB_CBR, // } (chave de fechamento)

    // Outros tokens
    EMPTY_STRING,   // String vazia ''
    STRING,         // String literals compostos por 'texto 232 sd'
    COMMENT,        // identificação de comentário
    EMPTY_COMMENT,  // comentário vazio
    IDENTIFIER,     // Identificadores
    NUM_INT,        // Número inteiro
    NUM_FLT,        // Número com pronto flutuante
    KEYWORD,        // Palavras reservadas
    UNKNOWN,        // Token desconhecida
    ERROR,          // Token inválida
    END_OF_FILE     // final do arquivo
} TokenType;

typedef struct Token
{
    TokenType type;
    char *value;
    struct Token *previous;
} Token;

int isKeyword(char *value)
{
    for (int i = 0; i < num_keywords; i++)
    {
        if (strcmp(value, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isValidIdentifier(char *value)
{
    int length = strlen(value);
    for (int i = 1; i < length; i++)
        if (!isalnum(value[i]) && value[i] != '_')
            return 0;
    return 1;
}

Token *getToken(FILE *file, Token *previousToken)
{
    int initial_size = 100;
    int resize_factor = 2;
    Token *token = (Token *)malloc(sizeof(Token));
    token->value = (char *)malloc(initial_size * sizeof(char));
    token->previous = previousToken;
    char ch;
    int index = 0;
    int is_float = 0;

    do
    {
        ch = fgetc(file);
        if (ch == EOF)
        {
            token->type = END_OF_FILE;
            strcpy(token->value, "EOF");
            return token;
        }
    } while (isspace(ch));


    // verifica se é uma string
    if (ch == '\'')
    {
        token->value[index++] = '\''; // adicionando abertura da string.

        ch = fgetc(file);
        while (ch != '\'' && ch != EOF)
        {
            token->value[index++] = ch;

            if (index >= initial_size - 1)
            {
                initial_size *= resize_factor;
                token->value = (char *)realloc(token->value, initial_size * sizeof(char));
                if (!token->value)
                {
                    printf("Erro: falha ao realocar memoria.\n");
                    exit(1);
                }
            }

            ch = fgetc(file);
        }
        token->value[index++] = '\''; // adicionando fechamento da string.
        token->value[index] = '\0';

        if (index > 0 && strcmp(token->value, "''") != 0)
        {
            token->type = STRING;
            return token;
        }
        if (index == 0)
        {
            strcpy(token->value, "''");
            token->type = EMPTY_STRING;
            return token;
        }
    }


    // Código para identificar comentário
    // if (ch == '{' || ch == '(')
    // {
    //     if (ch == '(')
    //     {
    //         token->value[index] = ch;
    //         token->type = SMB_OPA;
    //         ch = fgetc(file);
    //         if (ch == '*')
    //         {
    //             token->value[index++] = '('; // adcionando abertura do comentário
    //             while (1)
    //             {
    //                 token->value[index++] = ch;

    //                 if (index >= initial_size - 1)
    //                 {
    //                     initial_size *= resize_factor;
    //                     token->value = (char *)realloc(token->value, initial_size * sizeof(char));
    //                     if (!token->value)
    //                     {
    //                         printf("Erro: falha ao realocar memoria.\n");
    //                         exit(1);
    //                     }
    //                 }

    //                 ch = fgetc(file);
    //                 if (ch == '*')
    //                 {
    //                     ch = fgetc(file);
    //                     if (ch == ')')
    //                     {
    //                         break; // Fim do comentário de bloco
    //                     }
    //                 }
    //             }
    //             token->value[index++] = '*'; // Adiciona o fechamento do comentário
    //             token->value[index++] = ')'; // Adiciona o fechamento do comentário
    //             token->value[index] = '\0';

    //             if (index > 2 && strcmp(token->value, "(**)") != 0)
    //             {
    //                 token->type = COMMENT;
    //                 return token;
    //             }
    //             else
    //             {
    //                 strcpy(token->value, "(**)");
    //                 token->type = EMPTY_COMMENT;
    //                 return token;
    //             }
    //         }
    //         ungetc(ch, file);
    //         return token;
    //     }
    //     else if (ch == '{')
    //     {
    //         // Início do comentário de bloco { ... }
    //         do
    //         {
    //             token->value[index++] = ch;

    //             if (index >= initial_size - 1)
    //             {
    //                 initial_size *= resize_factor;
    //                 token->value = (char *)realloc(token->value, initial_size * sizeof(char));
    //                 if (!token->value)
    //                 {
    //                     printf("Erro: falha ao realocar memoria.\n");
    //                     exit(1);
    //                 }
    //             }

    //             ch = fgetc(file);
    //         } while (ch != '}' && ch != EOF);

    //         token->value[index++] = ch; // Adiciona o fechamento do comentário
    //         token->value[index] = '\0';

    //         if (index > 2 && strcmp(token->value, "{}") != 0)
    //         {
    //             token->type = COMMENT;
    //             return token;
    //         }
    //         else
    //         {
    //             strcpy(token->value, "{}");
    //             token->type = EMPTY_COMMENT;
    //             return token;
    //         }
    //     }
    // }


    // verica se é uma palavra reservada ou um identificador
    if (isalpha(ch) || ch == '_')
    {
        do
        {
            token->value[index++] = ch;

            if (index >= initial_size - 1)
            {
                initial_size *= resize_factor;
                token->value = (char *)realloc(token->value, initial_size * sizeof(char));
                if (!token->value)
                {
                    printf("Erro: falha ao realocar memoria.\n");
                    exit(1);
                }
            }

            ch = fgetc(file);
        } while (isalnum(ch) || ch == '_');

        token->value[index] = '\0';
        ungetc(ch, file);

        if (isKeyword(token->value))
        {
            if (previousToken != NULL && previousToken->type == ERROR && isdigit(*previousToken->value))
            {
                printf("A palavra reservada %s%s e invalida, pois começa com um numero.\n", token->previous->value, token->value);
                free(previousToken);
                previousToken = NULL;
                token->type = ERROR;
            }
            else
                token->type = KEYWORD;
        }
        else if (isValidIdentifier(token->value))
        {
            if (previousToken != NULL && previousToken->type == ERROR && isdigit(*previousToken->value))
            {
                printf("O identificador %s%s e invalido, pois começa com um numero.\n", token->previous->value, token->value);
                free(previousToken);
                previousToken = NULL;
                token->type = ERROR;
            }
            else
                token->type = IDENTIFIER;
        }
        return token;
    }


    // verifica o número, caso tenha um caractere letra após retorna um erro que é tratado no código acima
    if (isdigit(ch))
    {
        do
        {
            token->value[index++] = ch;
            ch = fgetc(file);
        } while (isdigit(ch));

        if (ch == '.')
        {
            is_float = 1;
            token->value[index++] = ch;
            ch = fgetc(file);
            while (isdigit(ch))
            {
                token->value[index++] = ch;
                ch = fgetc(file);
            }
        }

        token->value[index] = '\0';
        ungetc(ch, file);

        ch = fgetc(file);
        if (isalpha(ch))
        {
            ungetc(ch, file);
            token->type = ERROR;
            return token;
        }
        else
        {
            ungetc(ch, file);
            token->type = is_float ? NUM_FLT : NUM_INT;
            return token;
        }
    }


    // determina os tokens para os caracteres especiais da linguagem
    switch (ch) // Não será feito tratamento da variavel ERROR dentro desse switch
    {
    case ':':
        ch = fgetc(file);
        if (ch == '=')
        {
            strcpy(token->value, ":=");
            token->type = OP_ASS;
            break;
        }
        strcpy(token->value, ":");
        token->type = SMB_COL;
        ungetc(ch, file);
        break;

    case '=':
        ch = fgetc(file);
        if (ch == '=')
        {
            strcpy(token->value, "==");
            token->type = UNKNOWN;
            break;
        }
        strcpy(token->value, "=");
        token->type = OP_EQ;
        ungetc(ch, file);
        break;

    case '>':
        ch = fgetc(file);
        if (ch == '=')
        {
            strcpy(token->value, ">=");
            token->type = OP_GE;
            break;
        }
        strcpy(token->value, ">");
        token->type = OP_GT;
        ungetc(ch, file);
        break;

    case '<':
        ch = fgetc(file);
        if (ch == '=')
        {
            strcpy(token->value, "<=");
            token->type = OP_LE;
            break;
        }
        if (ch == '>')
        {
            strcpy(token->value, "<>");
            token->type = OP_NE;
            break;
        }
        strcpy(token->value, "<");
        token->type = OP_LT;
        ungetc(ch, file);
        break;

    case '+':
        ch = fgetc(file);
        if (ch == '=')
        {
            strcpy(token->value, "+=");
            token->type = UNKNOWN;
            break;
        }
        strcpy(token->value, "+");
        token->type = OP_AD;
        ungetc(ch, file);
        break;

    case '-':
        ch = fgetc(file);
        if (ch == '=')
        {
            strcpy(token->value, "-=");
            token->type = UNKNOWN;
            break;
        }
        strcpy(token->value, "-");
        token->type = OP_MIN;
        ungetc(ch, file);
        break;

    case '*':
        ch = fgetc(file);
        if (ch == '=')
        {
            strcpy(token->value, "*=");
            token->type = UNKNOWN;
            break;
        }
        strcpy(token->value, "*");
        token->type = OP_MUL;
        ungetc(ch, file);
        break;

    case '/':
        ch = fgetc(file);
        if (ch == '=')
        {
            strcpy(token->value, "/=");
            token->type = UNKNOWN;
            break;
        }
        strcpy(token->value, "/");
        token->type = OP_DIV;
        ungetc(ch, file);
        break;

    case '{':
        strcpy(token->value, "{");
        token->type = SMB_OBR;
        break;

    case '}':
        strcpy(token->value, "}");
        token->type = SMB_CBR;
        break;

    case ',':
        strcpy(token->value, ",");
        token->type = SMB_COM;
        break;

    case ';':
        strcpy(token->value, ";");
        token->type = SMB_SEM;
        break;

    case '.':
        strcpy(token->value, ".");
        token->type = SMB_PTO;
        break;

    case '(':
        strcpy(token->value, "(");
        token->type = SMB_OPA;
        break;

    case ')':
        strcpy(token->value, ")");
        token->type = SMB_CPA;
        break;

    case '[':
        strcpy(token->value, "[");
        token->type = SMB_OBC;
        break;

    case ']':
        strcpy(token->value, "]");
        token->type = SMB_CBC;
        break;

    default:
        token->value[0] = ch;
        token->value[1] = '\0';
        token->type = UNKNOWN;
        break;
    }

    return token;
}

void printToken(Token *token)
{
    switch (token->type)
    {
    case IDENTIFIER:
        printf("IDENTIFIER: %s\n", token->value);
        break;

    case NUM_INT:
        printf("NUM_INT: %s\n", token->value);
        break;

    case NUM_FLT:
        printf("NUM_FLT: %s\n", token->value);
        break;

    case KEYWORD:
        printf("KEYWORD: %s\n", token->value);
        break;

    case OP_EQ:
        printf("OP_EQ: %s\n", token->value);
        break;

    case OP_GE:
        printf("OP_GE: %s\n", token->value);
        break;

    case OP_MUL:
        printf("OP_MUL: %s\n", token->value);
        break;

    case OP_NE:
        printf("OP_NE: %s\n", token->value);
        break;

    case OP_LE:
        printf("OP_LE: %s\n", token->value);
        break;

    case OP_DIV:
        printf("OP_DIV: %s\n", token->value);
        break;

    case OP_GT:
        printf("OP_GT: %s\n", token->value);
        break;

    case OP_AD:
        printf("OP_AD: %s\n", token->value);
        break;

    case OP_ASS:
        printf("OP_ASS: %s\n", token->value);
        break;

    case OP_LT:
        printf("OP_LT: %s\n", token->value);
        break;

    case OP_MIN:
        printf("OP_MIN: %s\n", token->value);
        break;

    case SMB_OBC:
        printf("SMB_OBC: %s\n", token->value);
        break;

    case SMB_COM:
        printf("SMB_COM: %s\n", token->value);
        break;

    case SMB_CBC:
        printf("SMB_CBC: %s\n", token->value);
        break;

    case SMB_SEM:
        printf("SMB_SEM: %s\n", token->value);
        break;

    case SMB_OPA:
        printf("SMB_OPA: %s\n", token->value);
        break;

    case SMB_CPA:
        printf("SMB_CPA: %s\n", token->value);
        break;

    case SMB_OBR:
        printf("SMB_OBR: %s\n", token->value);
        break;

    case SMB_CBR:
        printf("SMB_CBR: %s\n", token->value);
        break;

    case SMB_PTO:
        printf("SMB_PTO: %s\n", token->value);
        break;
    case SMB_COL:
        printf("SMB_COL: %s\n", token->value);
        break;

    case STRING:
        printf("STRING: %s\n", token->value);
        break;

    case EMPTY_STRING:
        printf("EMPTY_STRING: %s\n", token->value);
        break;

    // case COMMENT: 
    //     printf("COMMENT: %s\n", token->value);
    //     break;

    // case EMPTY_COMMENT:
    //     printf("EMPTY_COMMENT: %s\n", token->value);
    //     break;

    case UNKNOWN:
        printf("UNKNOWN: %s\n", token->value);
        break;

    case END_OF_FILE:
        printf("EOF\n");
        break;

    default: // descomente aqui caso queria que imprima todos os erros
             //   printf("\n\n\t ERROR %s\n\n", token->value);
        break;
    }
}

#endif
