# Relatório Técnico de Análise Léxica para MicroPascal

## Introdução 

Este relatório documenta a implementação de um compilador de análise léxica desenvolvido em linguagem C, sem o uso de geradores de analisadores léxicos, que converte código MicroPascal em tokens. A análise léxica identifica operadores, símbolos, números, palavras-chave e identificadores, seguindo um esquema de tokens predefinido.

## Estruturas e Funções Utilizadas

### Estrutura `Token`

A estrutura `Token` é usada para armazenar o tipo de token e seu valor associado.

```c
typedef struct {
    TokenType type;
    char value[100];
} Token;
```
**Campos:** 
* `type:` Armazena o tipo do token como um valor do enum TokenType. Isso define se o token é um operador, símbolo, número, palavra-chave ou identificador.
    
* `value:` Armazena o valor textual do token, como o nome de uma variável, um operador ou um número.

### Enum `TokenType`

O enum `TokenType` define todos os tipos possíveis de tokens que o analisador léxico pode reconhecer.

```c
typedef enum {
    ID, NUM_INT, NUM_FLT, PAL_RES, OP_EQ, OP_GE, OP_MUL, OP_NE, OP_LE, OP_DIV, OP_GT, OP_AD, OP_ASS, OP_LT, OP_MIN, SMB_OBC, SMB_COM, SMB_CBC, SMB_SEM, SMB_OPA, SMB_CPA, UNKNOWN, END_OF_FILE
} TokenType;
```

**Tipos de Tokens**  
Tipo              | Token Definida|
------------------|---------------|
Identificadores   |       ID      |  
Números           |    NUM_INT    | 
                       NUM_FLT    |  
Palavra Reservada |    PAL_RES    | 
Operadores        | OP_EQ, OP_GE, OP_MUL, OP_NE, OP_LE, OP_DIV, OP_GT, OP_AD, OP_ASS, OP_LT, OP_MIN |
Símbolos          |  SMB_OBC, SMB_COM, SMB_CBC, SMB_SEM, SMB_OPA, SMB_CPA


Números: NUM_INT, NUM_FLT

* Palavras-chave: PAL_RES

* Operadores: OP_EQ, OP_GE, OP_MUL, OP_NE, OP_LE, OP_DIV, OP_GT, OP_AD, OP_ASS, OP_LT, OP_MIN

Símbolos: SMB_OBC, SMB_COM, SMB_CBC, SMB_SEM, SMB_OPA, SMB_CPA

Token desconhecido: UNKNOWN
Fim de arquivo: END_OF_FILE