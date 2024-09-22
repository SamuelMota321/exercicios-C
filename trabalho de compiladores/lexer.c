#include <stdio.h>
#include <ctype.h>
#include "lexer.h"
#include <stdlib.h>

int main()
{
    int option;
    FILE *file = NULL;
    Token *token = NULL;

    do
    {

        printf(" Compilador Lexico \n\n");
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

        switch (option)
        {
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            file = fopen("./codePas/calculoSimples.pas", "r");
            break;
        case 2:
            file = fopen("./codePas/estruturaCondicional.pas", "r");
            break;
        case 3:
            file = fopen("./codePas/lacoFor.pas", "r");
            break;
        case 4:
            file = fopen("./codePas/identificadorInvalido.pas", "r");
            break;
        case 5:
            file = fopen("./codePas/caractereDesconhecido.pas", "r");
            break;
        case 6:
            file = fopen("./codePas/operadorDesconhecido.pas", "r");
            break;
        case 7:
            file = fopen("./codePas/testeCompletoMicroPascal.pas", "r");
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
                printToken(token);
            } while (token->type != END_OF_FILE);
        }

    } while (option != 0);

    if (file != NULL)
    {
        fclose(file);
    }

    return 0;
}
