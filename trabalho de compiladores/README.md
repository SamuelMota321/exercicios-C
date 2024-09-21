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
* `type`: Armazena o tipo do token como um valor do enum TokenType. Isso define se o token é um operador, símbolo, número, palavra-chave ou identificador.
    
* `value`: Armazena o valor textual do token, como o nome de uma variável, um operador ou um número.

### Enum `TokenType`

O enum `TokenType` define todos os tipos possíveis de tokens que o analisador léxico pode reconhecer.

```c
typedef enum {
    ID, NUM_INT, NUM_FLT, PAL_RES, OP_EQ, OP_GE, OP_MUL, OP_NE, OP_LE, OP_DIV, OP_GT, OP_AD, OP_ASS, OP_LT, OP_MIN, SMB_OBC, SMB_COM, SMB_CBC, SMB_SEM, SMB_OPA, SMB_CPA, UNKNOWN, END_OF_FILE
} TokenType;
```

**Tipos de Tokens**  
| Tipo                 | Token Definida                                                                  |
| -------------------- | ------------------------------------------------------------------------------- |
| Identificadores      | ID                                                                              |
| Números              | NUM_INT,NUM_FLT                                                                 |
| Palavra Reservada    | PAL_RES                                                                         |
| Operadores           | OP_EQ, OP_GE, OP_MUL, OP_NE, OP_LE, OP_DIV, OP_GT, OP_AD, OP_ASS, OP_LT, OP_MIN |
| Símbolos             | SMB_OBC, SMB_COM, SMB_CBC, SMB_SEM, SMB_OPA, SMB_CPA                            |
| Tokens desconhecidas | UNKNOWN                                                                         |
| Fim do Arquivo       | END_OF_FILE                                                                     |

**Mais detalhes**

**Operadores:**
* OP_EQ: =
* OP_GE: >=
* OP_MUL: *
* OP_NE: <>
* OP_LE: <=
* OP_DIV: /
* OP_GT: >
* OP_AD: +
* OP_ASS: =
* OP_LT: <
* OP_MIN: -
  
**Símbolos:**
* SMB_OBC: {
* SMB_COM: ,
* SMB_CBC: }
* SMB_SEM: ;
* SMB_OPA: (
* SMB_CPA: )

### Função `is_keyword`

A função `is_keyword` verifica se uma string é uma palavra-chave definida na linguagem MicroPascal.

```c
int is_keyword(char *word) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
```

**Parâmetro:**
* `word`: String que será verificada.
  
**Retorno:**
* Retorna `1` se a string for uma palavra-chave; caso contrário, retorna `0`.

### Função `next_token`

Essa função é responsável por gerar o próximo token lido do arquivo.

```c
Token next_token(FILE *file) {
    // Implementação detalhada no código
}
```
**Parâmetro:**
* `file`: Ponteiro para o arquivo de código-fonte (programa MicroPascal) que está sendo lido.
  
**Retorno:**
* Retorna um Token contendo o tipo de token e o valor associado.

**Funcionamento:**
1. Ignora espaços em branco.
2. Detecta identificadores e palavras-chave.
3. Detecta números inteiros e reais.
4. Identifica operadores e símbolos.
5. Retorna o token gerado ou END_OF_FILE ao final.

### Função `print_token`

A função `print_token` imprime um token no formato adequado, identificando o tipo e valor do token.
```c
void print_token(Token token) {
    // Implementação detalhada no código
}
```

**Parâmetro:**
* `token`: O token a ser impresso.