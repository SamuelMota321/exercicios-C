# Relatório Técnico de Análise Léxica para MicroPascal

## Introdução 

Este relatório documenta a implementação de um compilador de análise léxica desenvolvido em linguagem C, sem o uso de geradores de analisadores léxicos, que converte código MicroPascal em tokens. A análise léxica identifica operadores, símbolos, números, palavras-chave e identificadores, seguindo um esquema de tokens predefinido.

## Estruturas e Funções Utilizadas

### Estrutura `Token`

A estrutura `Token` é usada para armazenar o tipo de token e seu valor associado.

```c
typedef struct {
    TokenType type;
    char *value;
    struct Token *previous;
} Token;
```
**Campos:** 
* `type`: Armazena o tipo do token como um valor do enum TokenType. Isso define se o token é um operador, símbolo, número, palavra-chave ou identificador.
    
* `value`: Armazena o valor textual do token, como o nome de uma variável, um operador ou um número.

* `Previous`: Armazena o valor do token anterior, como o objetivo de melhorar a tratativa de erros.

### Enum `TokenType`

O enum `TokenType` define todos os tipos possíveis de tokens que o analisador léxico pode reconhecer.

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
    EMPTY_STRING, // String vazia ''
    STRING,       // String literals compostos por 'texto 232 sd'
    IDENTIFIER,   // Identificadores
    NUM_INT,      // Número inteiro
    NUM_FLT,      // Número com pronto flutuante
    KEYWORD,      // Palavras reservadas
    UNKNOWN,      // Token desconhecida
    ERROR,        // Token inválida
    END_OF_FILE   // final do arquivo
} TokenType;

**Tipos de Tokens**  
| Tipo                 | Token Definida                                                                            |
| -------------------- | ----------------------------------------------------------------------------------------- |
| Identificadores      | IDENTIFIER                                                                                |
| Números              | NUM_INT,NUM_FLT                                                                           |
| Palavra Reservada    | KEYWORD                                                                                   |
| Operadores           | OP_EQ, OP_GE, OP_MUL, OP_NE, OP_LE, OP_DIV, OP_GT, OP_AD, OP_ASS, OP_LT, OP_MIN           |
| Símbolos             | SMB_SEM, SMB_COL, SMB_COM, SMB_PTO, SMB_OPA, SMB_CPA, SMB_OBC, SMB_CBC, SMB_OBR, SMB_CBR, |
| Erros                | ERROR                                                                                     |
| Texto                | STRING,  EMPTY_STRING                                                                     |
| Tokens desconhecidas | UNKNOWN                                                                                   |
| Fim do Arquivo       | END_OF_FILE                                                                               |


### Função `is_keyword`

A função `is_keyword` verifica se uma string é uma palavra-chave definida na linguagem MicroPascal.

```c
int isKeyword(char *value) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(value, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
```

**Parâmetro:**
* `value`: String que será verificada.
  
**Retorno:**
* Retorna `1` se a string for uma palavra-chave; caso contrário, retorna `0`.

### Função `isValidIdentifier`

A função `isValidIdentifier` verifica se uma string segue as regras de identificadores válidos da linguagem MicroPascal. 
Ela considera um identificador como válido se ele começa com uma letra ou sublinhado (`_`) 
e é seguido por letras, números ou sublinhados.

```c
int isValidIdentifier(char *value)
{
    int length = strlen(value);
    for (int i = 1; i < length; i++)
        if (!isalnum(value[i]) && value[i] != '_')
            return 0;
    return 1;
}
```

**Parâmetro:**

* `value`: A string que será verificada como identificador.

**Retorno:**

* Retorna `1` se for um identificador válido e `0` caso contrário.

**Funcionamento:**

1. Verifica se o primeiro caractere é uma letra ou sublinhado.
2. Itera pelos caracteres seguintes, validando que todos são alfanuméricos ou sublinhados.
3. Retorna o resultado da verificação


### Função `getToken`

Essa função é responsável por gerar o próximo token lido do arquivo.

```c
Token geToken(FILE *file, Token *previousToken) {
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

### Função `prinToken`

A função `prinToken` imprime um token no formato adequado, identificando o tipo e valor do token.
```c
void prinToken(Token token) {
    // Implementação detalhada no código
}
```

**Parâmetro:**
* `token`: O token a ser impresso.


## Testes Realizados

Foram realizados testes com sete programas, três corretos, três contendo erros de acordo com a gramática de MicroPascal e um mais longo e robusto para testar leitura de strings.

### Programas Corretos

**Programa 1: Cálculo Simples**
```pascal
begin
    x := 10;
    y := x + 5;
    writeln(y);
end.
``` 

**Análise Léxica:**

* Palavras-chave: `begin`, `end`.
* Identificadores: `x`, `y`, writeln
* Operadores: `:=`, `+`
* Números: `10`, `5`
* Símbolos: `(`, `)`, `;`, `.`

**Resultado esperado**: Tokens identificados corretamente, nenhum erro.

**Programa 2: Estrutura Condicional**
```pascal
begin
    if x > 10 then
        y := 20;
    else
        y := 0;
end.
```

**Análise Léxica:**

* Palavras-chave: `begin`, `if`, `then`, `else`, `end`.
* Identificadores: `x`, `y`
* Operadores: `>`, `:=`
* Números: `10`, `20`, `0`
* Símbolos: `;`, `.`

**Resultado esperado**: Tokens identificados corretamente, nenhum erro.

**Programa 3: Laço for**
```pascal
begin
    for i := 1 to 10 do
        writeln(i);
end.
``` 

**Análise Léxica:**

* Palavras-chave: `begin`, `for`, `to`, `do`, `end`.
* Identificadores: `i`, `writeln`
* Operadores: `:=`
* Números: `1`, `10`
* Símbolos: `;`, `.`

**Resultado esperado**: Tokens identificados corretamente, nenhum erro.

### Programas Incorretos

**Programa 4: Identificador Inválido**
```pascal
begin
    2x := 10;
end.
```

**Erro**: O identificador `2x` é inválido, pois começa com um número.

**Resultado esperado**: Erro de token `NUM_INT` precedendo o `ID`.

**Programa 5: Caractere desconhecido**
```pascal
begin
    x# := 10;
    y := 5;
end.
``` 
**Erro**: Símbolo desconhecido pela linguaguem `#`.

**Resultado esperado**: Erro léxico, símbolo desconhecido pela linguagem.

**Programa 6: Operador Desconhecido**
```pascal
begin
    x += 10;
end.
``` 
**Erro**: O operador += não é válido em MicroPascal, deveria ser :=.

**Resultado esperado**: Erro ao identificar o operador +=, geração de 2 tokens diferentes.


**Programa 7: Teste completo MicroPascal**
```pascal
program TesteCompiladorLexico;

var
    a, b, resultado: integer;
    x, y: real;
    condicao: boolean;

function SomaInteiros(i, j: integer): integer;
begin
    SomaInteiros := i + j;
end;

procedure MostraResultado(r: integer);
begin
    writeln('O resultado inteiro e: ', r);
end;

procedure MostraResultadoReal(r: real);
begin
    writeln('O resultado real e: ', r:0:2);
end;

begin
    a := 10;
    b := 20;
    x := 15.5;
    y := 25.75;
    condicao := true;

    resultado := a + b;
    MostraResultado(resultado);  

    resultado := a * (b - 5);
    MostraResultado(resultado);  

    y := x / 2.0;
    MostraResultadoReal(y);  

    if a > b then
        writeln('A e maior que B')
    else
        writeln('A e menor ou igual a B');

    while a < 15 do
    begin
        a := a + 1;
        writeln('Valor de A: ', a);
    end;

    resultado := SomaInteiros(a, b);
    MostraResultado(resultado);  

    condicao := (a = b);
    if condicao then
        writeln('A e igual a B')
    else
        writeln('A e diferente de B');

    if (a mod 2 = 0) then
        writeln('A e par')
    else
        writeln('A e impar');
        
end.

``` 
**Resultado esperado**: Tokens identificados corretamente, nenhum erro.


## Observações

### Sobre comentário em MicroPascal

Durante a execução do trabalho percebemos que a linguaguem de MicroPascal suporta comentários. Mas conforme especificado no trabalho:

Outras características de MicroPascal
* As palavras-chave de MicroPascal são reservadas;
* Toda variável deve ser declarada antes do seu uso;
* **A linguagem não permite o uso de comentários;**
* A semântica dos demais comandos e expressões e a tradicional do Pascal;
* A linguagem não é case-sensitive;

Entretanto decidimos que seria interessante deixar um código preparado(comentado) que faz a tratativa de comentários em pascal. 

