# Relatório Técnico de Análise Léxica para MicroPascal

## Introdução 

Este relatório documenta a implementação de um compilador de análise léxica desenvolvido em linguagem C, sem o uso de geradores de analisadores léxicos, que converte código MicroPascal em tokens. A análise léxica identifica operadores, símbolos, números, palavras-chave e identificadores, seguindo um esquema de tokens predefinido.


# tokens.h
## Estruturas e Funções Utilizadas

### Enumeração `TokenType`

A enumeração `TokenType` define os diferentes tipos de tokens que o analisador pode reconhecer. Os tipos de tokens incluem operadores, delimitadores, identificadores, números, strings, palavras-chave e outros tipos de tokens.

#### Tipos de Tokens

- **Operadores Aritméticos**:
  - `OP_AD`: Adição (`+`)
  - `OP_MIN`: Subtração (`-`)
  - `OP_MUL`: Multiplicação (`*`)
  - `OP_DIV`: Divisão (`/`)

- **Operadores de Comparação**:
  - `OP_EQ`: Igualdade (`=`)
  - `OP_NE`: Diferença (`<>`)
  - `OP_GT`: Maior que (`>`)
  - `OP_LT`: Menor que (`<`)
  - `OP_GE`: Maior ou igual (`>=`)
  - `OP_LE`: Menor ou igual (`<=`)

- **Operador de Atribuição**:
  - `OP_ASS`: Atribuição (`:=`)

- **Delimitadores**:
  - `SMB_SEM`: Ponto e vírgula (`;`)
  - `SMB_COL`: Dois pontos (`:`)
  - `SMB_COM`: Vírgula (`,`)
  - `SMB_PTO`: Ponto (`.`)

- **Parênteses e Colchetes**:
  - `SMB_OPA`: Parênteses de abertura (`(`)
  - `SMB_CPA`: Parênteses de fechamento (`)`)
  - `SMB_OBC`: Colchete de abertura (`[`)
  - `SMB_CBC`: Colchete de fechamento (`]`)
  
- **Chaves**:
  - `SMB_OBR`: Chave de abertura (`{`)
  - `SMB_CBR`: Chave de fechamento (`}`)

- **Outros Tokens**:
  - `EMPTY_STRING`: String vazia (`''`)
  - `STRING`: Literais de string
  - `COMMENT`: Comentários
  - `EMPTY_COMMENT`: Comentário vazio
  - `IDENTIFIER`: Identificadores
  - `NUM_INT`: Números inteiros
  - `NUM_FLT`: Números com ponto flutuante
  - `KEYWORD`: Palavras reservadas
  - `UNKNOWN`: Token desconhecido
  - `ERROR`: Token inválido
  - `END_OF_FILE`: Final do arquivo

### Estrutura `Token`

A estrutura `Token` representa um token individual, contendo as seguintes informações:

- **TokenType `type`**: O tipo do token.
- **char *value**: O valor do token, como a sequência de caracteres que representa o token.
- **struct Token *previous**: Um ponteiro para o token anterior na lista encadeada de tokens.
- **struct Token *next**: Um ponteiro para o próximo token na lista encadeada de tokens.

## Palavras-chave

Uma lista de palavras-chave válidas é definida como um array de strings. As palavras-chave são termos reservados que têm um significado especial na linguagem de programação.

```c
char *keywords[] = {"and", "array", "begin", "case", "const", "div", "do", "downto", "else", "end", 
                    "for", "function", "if", "in", "integer", "label", "mod", "not", "of", 
                    "or", "procedure", "program", "record", "repeat", "set", "then", "to", 
                    "type", "var", "while", "with"};
int num_keywords = 31;
```



# Lexer.h

Este arquivo contém a implementação do analisador léxico (lexer) para um compilador, que é responsável por ler um arquivo de entrada e dividir seu conteúdo em tokens.

## Estruturas e Variáveis Globais

### Variáveis Globais

- `int initial_size`: Tamanho inicial do buffer de memória para tokens.
- `int resize_factor`: Fator de redimensionamento para aumentar o tamanho do buffer.
- `int current_line`: Linha atual do arquivo sendo analisado.
- `int current_column`: Coluna atual do arquivo sendo analisado.

## Funções

### `int isKeyword(char *value)`

Verifica se a string fornecida é uma palavra-chave válida da linguagem.

#### Parâmetros
- `char *value`: A string a ser verificada.

#### Retorno
- `1` se for uma palavra-chave, `0` caso contrário.

---

### `int isValidIdentifier(char *value)`

Verifica se a string fornecida é um identificador válido.

#### Parâmetros
- `char *value`: A string a ser verificada.

#### Retorno
- `1` se for um identificador válido, `0` caso contrário.

---

### `void reallocMemory( Token *token, int index)`

Realoca a memória para o valor do token.

#### Parâmetros
- `Token *token`: O token cuja memória será realocada.
- `int index`: O índice atual no buffer do token.
---

### `const char *tokenTypeToString(TokenType type)`

Converte o tipo de token em uma string legível.

#### Parâmetros
- `TokenType type`: O tipo do token.

#### Retorno
- Uma string representando o tipo do token.

---

### `Token *handleErrors(Token *token, const char *errorMessage, ...)`

Manipula erros durante a análise léxica.

#### Parâmetros
- `Token *token`: O token que está sendo processado.
- `const char *errorMessage`: A mensagem de erro a ser formatada.
- `...`: os argumentos que serão printados junto a mensagem.

#### Retorno
- O token modificado com o tipo de erro.

---

### `Token *isString(FILE *file, char ch, Token *token, int index)`

Verifica se o caractere atual representa o início de uma string.

#### Parâmetros
- `FILE *file`: O arquivo de entrada.
- `char ch`: O caractere atual.
- `Token *token`: O token a ser preenchido.
- `int index`: O índice atual no buffer do token.

#### Retorno
- O tipo de token string.

---

### `Token *isAComment(FILE *file, char ch, Token *token, int index)`

Verifica se o caractere atual representa o início de um comentário.

#### Parâmetros
- `FILE *file`: O arquivo de entrada.
- `char ch`: O caractere atual.
- `Token *token`: O token a ser preenchido.
- `int index`: O índice atual no buffer do token.

#### Retorno
- O tipo de token comment.

---

### `Token *isAKeywordOrIdentifier(FILE *file, char ch, Token *token, int index, Token *previousToken)`

Classifica o caractere atual como uma palavra-chave ou identificador.

#### Parâmetros
- `FILE *file`: O arquivo de entrada.
- `char ch`: O caractere atual.
- `Token *token`: O token a ser preenchido.
- `int index`: O índice atual no buffer do token.
- `Token *previousToken`: O token anterior.

#### Retorno
- IDENTIFIER ou KEYWORD.
- caso não seja nenhuma das opções entra no tratamento de erros.

---

### `Token *isANumber(FILE *file, char ch, Token *token, int index)`

Verifica se o caractere atual representa um número.

#### Parâmetros
- `FILE *file`: O arquivo de entrada.
- `char ch`: O caractere atual.
- `Token *token`: O token a ser preenchido.
- `int index`: O índice atual no buffer do token.

#### Retorno
- O token preenchido.
- Um erro caso o próximo caractere não seja um espaço em branco ou outro numero. 

---

### `Token *getToken(FILE *file, Token *previousToken)`

Obtém o próximo token do arquivo.

#### Parâmetros
- `FILE *file`: O arquivo de entrada.
- `Token *previousToken`: O token anterior.

#### Retorno
- O próximo token lido do arquivo.

---

### `void printToken(Token *token)`

Imprime todos os tokens do arquivo em tempo de compilação.

#### Parâmetros
- `Token *token`: O token a ser impresso.

---

### `void printList(Token *Initialtoken)`

Imprime todos os tokens com base na lista salva na memória. 
**Obs**: para a execução se encontrar tokens de erro ou desconhecidas.

#### Parâmetros
- `Token *Initialtoken`: O token inicial da lista.



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
    222x := 10;
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

