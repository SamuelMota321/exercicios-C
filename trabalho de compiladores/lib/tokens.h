#ifndef TOKENS_H
#define TOKENS_H

char *keywords[] = {"and", "array", "begin", "case", "const", "div", "do", "downto", "else", "end", "for",
                    "function", "if", "in", "integer", "label", "mod", "not", "of", "or", "procedure", "program", "record", "repeat",
                    "set", "then", "to", "type", "var", "while", "with"};
int num_keywords = 31;

// Definindo uma macro com os tipos de tokens e suas representações
#define TOKEN_TYPES                                                     \
    X(OP_AD)  /* + */                                                   \
    X(OP_MIN) /* - */                                                   \
    X(OP_MUL) /* * */                                                   \
    X(OP_DIV) /* / */                                                   \
    /* Operadores de Comparação */                                    \
    X(OP_EQ) /* = */                                                    \
    X(OP_NE) /* <> */                                                   \
    X(OP_GT) /* > */                                                    \
    X(OP_LT) /* < */                                                    \
    X(OP_GE) /* >= */                                                   \
    X(OP_LE) /* <= */                                                   \
    /* Operador de Atribuição */                                      \
    X(OP_ASS) /* := */                                                  \
    /* Delimitadores */                                                 \
    X(SMB_SEM) /* ; */                                                  \
    X(SMB_COL) /* : */                                                  \
    X(SMB_COM) /* , */                                                  \
    X(SMB_PTO) /* . (ponto, para finalização) */                      \
    /* Parênteses e Colchetes */                                       \
    X(SMB_OPA) /* ( (parênteses de abertura) */                        \
    X(SMB_CPA) /* ) (parênteses de fechamento) */                      \
    X(SMB_OBC) /* [ (colchete de abertura) */                           \
    X(SMB_CBC) /* ] (colchete de fechamento) */                         \
    /* Chaves */                                                        \
    /* X(SMB_OBR)   { (chave de abertura) */                            \
    /*X(SMB_CBR)   } (chave de fechamento) */                           \
    /* Outros tokens */                                                 \
    X(EMPTY_STRING)  /* String vazia '' */                              \
    X(STRING)        /* String literals compostos por 'texto 232 sd' */ \
    X(COMMENT)       /* identificação de comentário */               \
    X(EMPTY_COMMENT) /* comentário vazio */                            \
    X(IDENTIFIER)    /* Identificadores */                              \
    X(NUM_INT)       /* Número inteiro */                              \
    X(NUM_FLT)       /* Número com ponto flutuante */                  \
    X(KEYWORD)       /* Palavras reservadas */                          \
    X(UNKNOWN)       /* Token desconhecido */                           \
    X(ERROR)         /* Token inválido */                              \
    X(END_OF_FILE)   /* final do arquivo */

// Gerando a enum a partir dos tokens definidos acima
typedef enum
{
#define X(token) token,
    TOKEN_TYPES
#undef X
} TokenType;


typedef struct Token
{
    TokenType type;
    char *value;
    struct Token *previous;
    struct Token *next;
    int line;
    int colunm;
} Token;
typedef struct Table
{
    int id;
    Token *identifier;
    struct Table *nextIdentifier;
} Table;
#endif