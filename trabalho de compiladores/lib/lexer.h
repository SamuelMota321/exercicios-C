#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>
#include "tokens.h"
#include <direct.h>

int initial_size = 100;
int resize_factor = 2;
int current_line = 1;
int current_column = 1;

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

void reallocMemory(Token *token, int index)
{
    int newSize = initial_size + (int)(index / 3);
    token->value = (char *)realloc(token->value, newSize * sizeof(char));
    if (!token->value)
    {
        printf("Erro: falha ao realocar memoria.\n");
        exit(1);
    }
}

const char *tokenTypeToString(TokenType type)
{
    switch (type)
    {
#define X(token) \
    case token:  \
        return #token;
        TOKEN_TYPES
#undef X
    default:
        printf("Unexpected error");
        break;
    }
}

Token *handleErrors(Token *token, const char *errorMessage, ...)
{
    va_list args;
    va_start(args, errorMessage); // Inicializa a lista de argumentos
    fprintf(stderr, "\nErro encontrado na linha %d, coluna %d: ", current_line, current_column);
    vprintf(errorMessage, args); // Imprime a mensagem de erro formatada com os argumentos variáveis
    va_end(args);                // Finaliza o uso da lista de argumentos
    token->type = ERROR;         // Define o tipo do token como erro
    return token;
}

Token *isString(FILE *file, char ch, Token *token, int index)
{
    token->value[index++] = '\''; // adicionando abertura da string

    ch = fgetc(file);
    while (ch != '\'' && ch != EOF)
    {
        token->value[index++] = ch;

        if (index >= initial_size - 1)
            reallocMemory(token, index);

        ch = fgetc(file);
    }
    token->value[index++] = '\''; // adicionando fechamento da string
    token->value[index] = '\0';

    if (index > 0 && strcmp(token->value, "''") != 0)
    {
        token->type = STRING;
    }

    if (index == 0)
    {
        strcpy(token->value, "''");
        token->type = EMPTY_STRING;
    }
    return token;
}

Token *isAComment(FILE *file, char ch, Token *token, int index)
{
    if (ch == '(')
    {
        token->value[index++] = ch;
        token->type = SMB_OPA;
        ch = fgetc(file);
        if (strchr("*", ch))
        {
            token->value[index++] = '('; // adcionando abertura do comentário
            while (1 || ch != EOF)
            {
                token->value[index++] = ch;

                if (index >= initial_size - 1)
                    reallocMemory(token, index);

                ch = fgetc(file);
                if (ch == '*')
                {
                    ch = fgetc(file);
                    if (ch == ')')
                    {
                        break; // Fim do comentário de bloco
                    }
                }
            }
            token->value[index++] = '*'; // Adiciona o fechamento do comentário
            token->value[index++] = ')'; // Adiciona o fechamento do comentário
            token->value[index] = '\0';

            if (index > 2 && strcmp(token->value, "(**)") != 0)
            {
                token->type = COMMENT;
                return token;
            }
            else
            {
                strcpy(token->value, "(**)");
                token->type = EMPTY_COMMENT;
                return token;
            }
        }
        ungetc(ch, file);
        token->value[index] = '\0';
        return token;
    }
    else
    {
        // Início do comentário de bloco { ... }
        do
        {
            token->value[index++] = ch;

            if (index >= initial_size - 1)
                reallocMemory(token, index);

            ch = fgetc(file);
        } while (ch != '}' && ch != EOF);

        token->value[index++] = ch; // Adiciona o fechamento do comentário
        token->value[index] = '\0';

        if (index > 2 && strcmp(token->value, "{}") != 0)
        {
            token->type = COMMENT;
            return token;
        }
        else
        {
            strcpy(token->value, "{}");
            token->type = EMPTY_COMMENT;
            return token;
        }
    }
}

Token *isAKeywordOrIdentifier(FILE *file, char ch, Token *token, int index, Token *previousToken)
{
    do
    {
        token->value[index++] = ch;

        if (index >= initial_size - 1)
            reallocMemory(token, index);

        ch = fgetc(file);
    } while (isalnum(ch) || ch == '_');

    ungetc(ch, file);
    token->value[index] = '\0';

    if (isKeyword(token->value))
    {
        if (previousToken != NULL && previousToken->type == ERROR && isdigit(*previousToken->value))
        {
            token = handleErrors(token, "A palavra reservada %s%s e invalida.\n", token->previous->value, token->value);
        }
        else
            token->type = KEYWORD;
    }
    else if (isValidIdentifier(token->value))
    {
        if (previousToken != NULL && previousToken->type == ERROR && isdigit(*previousToken->value))
        {
            token = handleErrors(token, "O identificador %s%s e invalido.\n", token->previous->value, token->value);
        }
        else
            token->type = IDENTIFIER;
    }
    return token;
}

Token *isANumber(FILE *file, char ch, Token *token, int index)
{
    int is_float = 0;
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

Token *getToken(FILE *file, Token *previousToken)
{
    Token *token = (Token *)malloc(sizeof(Token));
    token->value = (char *)malloc(initial_size * sizeof(char));
    token->previous = previousToken; // O token atual aponta para o anterior
    token->next = NULL;              // O próximo token ainda não existe, então é NULL
    if (previousToken != NULL)
    {
        previousToken->next = token; // O token anterior aponta para o token atual
    }

    char ch;
    int index = 0;

    while (1)
    {
        ch = fgetc(file);
        if (ch == EOF)
        {
            token->type = END_OF_FILE;
            strcpy(token->value, "EOF");
            return token;
        }

        // Atualiza a linha e a coluna
        if (ch == '\n')
        {
            current_line++;
            current_column = 0; // Reinicia a coluna na nova linha
        }
        else if (!isspace(ch))
        {
            // Se não for espaço em branco, conta a coluna
            current_column++;
            break; // Sai do loop para processar o próximo caractere
        }
        else
        {
            // Se for espaço em branco, apenas incrementa a coluna
            current_column++;
        }
    }

    // Verifica se é uma string
    if (ch == '\'')
    {
        token = isString(file, ch, token, index);
        token->line = current_line;
        token->colunm = current_column;
        return token;
    }

    // Código para identificar comentário
    if (ch == '{' || ch == '(')
    {
        token = isAComment(file, ch, token, index);
        token->line = current_line;
        token->colunm = current_column;
        return token;
    }

    // Verifica se é uma palavra reservada ou um identificador
    if (isalpha(ch) || ch == '_')
    {
        token = isAKeywordOrIdentifier(file, ch, token, index, previousToken);
        token->line = current_line;
        token->colunm = current_column;
        return token;
    }

    // Verifica se é um número
    if (isdigit(ch))
    {
        token = isANumber(file, ch, token, index);
        token->line = current_line;
        token->colunm = current_column;
        return token;
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

        // case '{':
        //     strcpy(token->value, "{");
        //     token->type = SMB_OBR;
        //     break;

        // case '}': //esta sendo tratado nos comentarios
        //     strcpy(token->value, "}");
        //     token->type = SMB_CBR;
        //     break;

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

        // o tratamento da leitura da abertura do parênteses está sendo feita no if que checa comentários
    // case '(':
    //     strcpy(token->value, "(");
    //     token->type = SMB_OPA;
    //     break;
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

    token->line = current_line;
    token->colunm = current_column;
    return token;
}

void ensureOutputDirectoryExists()
{
    struct stat st = {0};

    // Se o diretório ./output/ não existir, crie-o
    if (stat("./output", &st) == -1)
    {
        mkdir("./output");
    }
}

Table *createNodeTable(Token *token)
{
    static int index = 1;
    Table *newNode = (Table *)malloc(sizeof(Table));
    newNode->id = index++;
    newNode->identifier = token;
    newNode->nextIdentifier = NULL;
}

void printTable(Token *token, Table **table)
{
    Token *currentToken = token;

    while (currentToken != NULL)
    {
        if (currentToken->type == IDENTIFIER)
        {
            Table *current = *table;
            int found = 0;

            // Procura na tabela para ver se o identificador já existe
            while (current != NULL)
            {
                if (current->identifier->type == currentToken->type &&
                    strcmp(current->identifier->value, currentToken->value) == 0)
                {
                    printf("| Linha %d | Coluna: %d | index: %d | token: %s | Value:  %s | \n", currentToken->line, currentToken->colunm, current->id, tokenTypeToString(currentToken->type), currentToken->value);
                    found = 1;
                    break;
                }
                current = current->nextIdentifier;
            }

            // Se não foi encontrado, adiciona um novo nó na tabela
            if (!found)
            {
                Table *newNode = createNodeTable(currentToken);
                if (*table == NULL)
                {
                    *table = newNode;
                }
                else
                {
                    current = *table;
                    while (current->nextIdentifier != NULL)
                    {
                        current = current->nextIdentifier;
                    }
                    current->nextIdentifier = newNode;
                }
                printf("| Linha %d | Coluna: %d | index: %d | token: %s | Value:  %s | \n", currentToken->line, currentToken->colunm, newNode->id, tokenTypeToString(currentToken->type), currentToken->value);
            }
        }
        currentToken = currentToken->next;
    }
}

// printando a partir do token inicial da lista
void printFile(Token *Initialtoken, FILE *file)
{
    Token *temp = Initialtoken;
    if (!file)
    {
        printf("Erro ao abrir o arquivo de saida!\n\n");
    }
    else
    {
        printf("\nImprimindo arquivo de saida\n");
        while (temp != NULL)
        {
            switch (temp->type)
            {
            case ERROR:
                fprintf(file, "%s : %s  erro identificado! encontrado na linha %d coluna %d\n", tokenTypeToString(temp->type), temp->value, current_line, current_column);
                break;

            case UNKNOWN:
                fprintf(file, "%s : %s  token desconhecido pela linguagem! encontrado na linha %d coluna %d\n", tokenTypeToString(temp->type), temp->value, current_line, current_column);
                printf("\n%s : %s  token desconhecido pela linguagem! encontrado na linha %d coluna %d\n\n", tokenTypeToString(temp->type), temp->value, current_line, current_column);
                break;

            default:
                fprintf(file, "Linha %d coluna %d <%s, %s> \n", temp->line, temp->colunm, temp->value, tokenTypeToString(temp->type));
                break;
            }
            temp = temp->next;
        }
    }
}

#endif