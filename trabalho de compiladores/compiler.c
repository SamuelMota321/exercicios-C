#include <stdio.h>
#include <ctype.h>
#include "lib/lexer.h"
#include "lib/syntactic.h"
#include <stdlib.h>

int main()
{
    ensureOutputDirectoryExists();
    int option;
    FILE *file = NULL;
    FILE *fileExit = NULL; // Declaração do arquivo de saída

    do
    {
        int index = 0;
        Token *token = NULL;
        Token *initialToken = NULL;
        Table *table = NULL;
        Table *initialIdentifier = NULL;

        printf(" \n Compilador Lexico \n\n");
        printf(" Selecione um dos testes a seguir \n\n");
        printf(" Testes corretos \n\n");
        printf(" \t1 - Calculo simples \n");
        printf(" \t2 - Estrutura condicional \n");
        printf(" \t3 - Laco for \n\n");
        printf(" Testes que retornam erros \n\n");
        printf(" \t4 - Identificador Invalido \n");
        printf(" \t5 - Caractere desconhecido \n");
        printf(" \t6 - Operador desconhecido \n\n");
        printf(" Teste mais robusto \n\n");
        printf(" \t7 - Teste completo micro pascal \n");
        printf(" \t0 - Sair \n");
        scanf("%d", &option);

        if (getchar() != '\n')
        {
            printf("Entrada invalida. Por favor, insira um numero.\n");
            while (getchar() != '\n') // Limpa a entrada até a nova linha
                ;
            continue;
        }

        if (file != NULL)
        {
            fclose(file);
            file = NULL;
        }

        if (fileExit != NULL)
        {
            fclose(fileExit); // Fechando o arquivo de saída anterior
            fileExit = NULL;
        }

        switch (option)
        {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            file = fopen("./codePas/calculoSimples.pas", "r");
            fileExit = fopen("./output/calculoSimples.lex", "w");
            break;
        case 2:
            file = fopen("./codePas/estruturaCondicional.pas", "r");
            fileExit = fopen("./output/estruturaCondicional.lex", "w");
            break;
        case 3:
            file = fopen("./codePas/lacoFor.pas", "r");
            fileExit = fopen("./output/lacoFor.lex", "w");
            break;
        case 4:
            file = fopen("./codePas/identificadorInvalido.pas", "r");
            fileExit = fopen("./output/identificadorInvalido.lex", "w");
            break;
        case 5:
            file = fopen("./codePas/caractereDesconhecido.pas", "r");
            fileExit = fopen("./output/caractereDesconhecido.lex", "w");
            break;
        case 6:
            file = fopen("./codePas/operadorDesconhecido.pas", "r");
            fileExit = fopen("./output/operadorDesconhecido.lex", "w");
            break;
        case 7:
            file = fopen("./codePas/testeCompletoMicroPascal.pas", "r");
            fileExit = fopen("./output/testeCompletoMicroPascal.lex", "w");
            break;
        default:
            printf("Opcao invalida\n");
            option = -1;
            continue;
        }

        if (file == NULL && option != 0)
        {
            printf("Erro ao abrir o arquivo.\n");
            continue;
        }

        if (option != 0)
        {
            do
            {
                token = getToken(file, token);
                if (token->previous == NULL)
                    initialToken = token;
            } while (token->type != END_OF_FILE);

            printFile(initialToken, fileExit); // Agora a lista de tokens é impressa no arquivo de saída
            
            // Chamada para iniciar o analisador sintático 
            Token *currentToken = initialToken; // Inicializa o token atual com o primeiro token da lista
            parseProgram(&currentToken); // Chama o analisador sintático com o token inicial

            printTable(initialToken, &table);
            // Resetando a contagem de linhas e colunas após a compilação
            current_line = 1;
            current_column = 1;
        }

    } while (option != 0);

    if (file != NULL)
    {
        fclose(file);
    }

    if (fileExit != NULL)
    {
        fclose(fileExit); // Certifique-se de fechar o arquivo de saída no final
    }

    return 0;
}
